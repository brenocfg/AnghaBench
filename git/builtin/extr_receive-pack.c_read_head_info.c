#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct packet_reader {int pktlen; int options; scalar_t__ status; int /*<<< orphan*/  line; } ;
struct oid_array {int dummy; } ;
struct object_id {int dummy; } ;
struct command {int dummy; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  LARGE_PACKET_MAX ; 
 int PACKET_READ_CHOMP_NEWLINE ; 
 scalar_t__ PACKET_READ_FLUSH ; 
 scalar_t__ PACKET_READ_NORMAL ; 
 scalar_t__ advertise_atomic_push ; 
 scalar_t__ advertise_push_options ; 
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ get_oid_hex (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,struct object_id*) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 scalar_t__ parse_feature_request (char const*,char*) ; 
 TYPE_1__ push_cert ; 
 struct command** queue_command (struct command**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_commands_from_cert (struct command**,TYPE_1__*) ; 
 int quiet ; 
 int report_status ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strbuf_addstr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int use_atomic ; 
 int use_push_options ; 
 int /*<<< orphan*/  use_sideband ; 

__attribute__((used)) static struct command *read_head_info(struct packet_reader *reader,
				      struct oid_array *shallow)
{
	struct command *commands = NULL;
	struct command **p = &commands;
	for (;;) {
		int linelen;

		if (packet_reader_read(reader) != PACKET_READ_NORMAL)
			break;

		if (reader->pktlen > 8 && starts_with(reader->line, "shallow ")) {
			struct object_id oid;
			if (get_oid_hex(reader->line + 8, &oid))
				die("protocol error: expected shallow sha, got '%s'",
				    reader->line + 8);
			oid_array_append(shallow, &oid);
			continue;
		}

		linelen = strlen(reader->line);
		if (linelen < reader->pktlen) {
			const char *feature_list = reader->line + linelen + 1;
			if (parse_feature_request(feature_list, "report-status"))
				report_status = 1;
			if (parse_feature_request(feature_list, "side-band-64k"))
				use_sideband = LARGE_PACKET_MAX;
			if (parse_feature_request(feature_list, "quiet"))
				quiet = 1;
			if (advertise_atomic_push
			    && parse_feature_request(feature_list, "atomic"))
				use_atomic = 1;
			if (advertise_push_options
			    && parse_feature_request(feature_list, "push-options"))
				use_push_options = 1;
		}

		if (!strcmp(reader->line, "push-cert")) {
			int true_flush = 0;
			int saved_options = reader->options;
			reader->options &= ~PACKET_READ_CHOMP_NEWLINE;

			for (;;) {
				packet_reader_read(reader);
				if (reader->status == PACKET_READ_FLUSH) {
					true_flush = 1;
					break;
				}
				if (reader->status != PACKET_READ_NORMAL) {
					die("protocol error: got an unexpected packet");
				}
				if (!strcmp(reader->line, "push-cert-end\n"))
					break; /* end of cert */
				strbuf_addstr(&push_cert, reader->line);
			}
			reader->options = saved_options;

			if (true_flush)
				break;
			continue;
		}

		p = queue_command(p, reader->line, linelen);
	}

	if (push_cert.len)
		queue_commands_from_cert(p, &push_cert);

	return commands;
}