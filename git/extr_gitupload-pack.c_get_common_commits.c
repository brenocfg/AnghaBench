#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct packet_reader {int /*<<< orphan*/  line; } ;
struct object_id {int dummy; } ;
struct object_array {scalar_t__ nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 scalar_t__ PACKET_READ_NORMAL ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int got_oid (char const*,struct object_id*,struct object_array*) ; 
 int multi_ack ; 
 scalar_t__ no_done ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oid_to_hex_r (char*,struct object_id*) ; 
 scalar_t__ ok_to_give_up (struct object_array*,struct object_array*) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  packet_write_fmt (int,char*,...) ; 
 int /*<<< orphan*/  reset_timeout () ; 
 scalar_t__ save_commit_buffer ; 
 scalar_t__ skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 scalar_t__ stateless_rpc ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_common_commits(struct packet_reader *reader,
			      struct object_array *have_obj,
			      struct object_array *want_obj)
{
	struct object_id oid;
	char last_hex[GIT_MAX_HEXSZ + 1];
	int got_common = 0;
	int got_other = 0;
	int sent_ready = 0;

	save_commit_buffer = 0;

	for (;;) {
		const char *arg;

		reset_timeout();

		if (packet_reader_read(reader) != PACKET_READ_NORMAL) {
			if (multi_ack == 2 && got_common
			    && !got_other && ok_to_give_up(have_obj, want_obj)) {
				sent_ready = 1;
				packet_write_fmt(1, "ACK %s ready\n", last_hex);
			}
			if (have_obj->nr == 0 || multi_ack)
				packet_write_fmt(1, "NAK\n");

			if (no_done && sent_ready) {
				packet_write_fmt(1, "ACK %s\n", last_hex);
				return 0;
			}
			if (stateless_rpc)
				exit(0);
			got_common = 0;
			got_other = 0;
			continue;
		}
		if (skip_prefix(reader->line, "have ", &arg)) {
			switch (got_oid(arg, &oid, have_obj)) {
			case -1: /* they have what we do not */
				got_other = 1;
				if (multi_ack && ok_to_give_up(have_obj, want_obj)) {
					const char *hex = oid_to_hex(&oid);
					if (multi_ack == 2) {
						sent_ready = 1;
						packet_write_fmt(1, "ACK %s ready\n", hex);
					} else
						packet_write_fmt(1, "ACK %s continue\n", hex);
				}
				break;
			default:
				got_common = 1;
				oid_to_hex_r(last_hex, &oid);
				if (multi_ack == 2)
					packet_write_fmt(1, "ACK %s common\n", last_hex);
				else if (multi_ack)
					packet_write_fmt(1, "ACK %s continue\n", last_hex);
				else if (have_obj->nr == 1)
					packet_write_fmt(1, "ACK %s\n", last_hex);
				break;
			}
			continue;
		}
		if (!strcmp(reader->line, "done")) {
			if (have_obj->nr > 0) {
				if (multi_ack)
					packet_write_fmt(1, "ACK %s\n", last_hex);
				return 0;
			}
			packet_write_fmt(1, "NAK\n");
			return -1;
		}
		die("git upload-pack: expected SHA1 list, got '%s'", reader->line);
	}
}