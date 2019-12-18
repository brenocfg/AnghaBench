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
struct packet_reader {scalar_t__ status; int /*<<< orphan*/  line; } ;
struct oidset {int dummy; } ;
struct object_id {int dummy; } ;
struct fetch_negotiator {int /*<<< orphan*/  (* ack ) (struct fetch_negotiator*,struct commit*) ;} ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ PACKET_READ_DELIM ; 
 scalar_t__ PACKET_READ_FLUSH ; 
 scalar_t__ PACKET_READ_NORMAL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  get_oid_hex (char const*,struct object_id*) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  oidset_insert (struct oidset*,struct object_id*) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  process_section_header (struct packet_reader*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct fetch_negotiator*,struct commit*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int process_acks(struct fetch_negotiator *negotiator,
			struct packet_reader *reader,
			struct oidset *common)
{
	/* received */
	int received_ready = 0;
	int received_ack = 0;

	process_section_header(reader, "acknowledgments", 0);
	while (packet_reader_read(reader) == PACKET_READ_NORMAL) {
		const char *arg;

		if (!strcmp(reader->line, "NAK"))
			continue;

		if (skip_prefix(reader->line, "ACK ", &arg)) {
			struct object_id oid;
			if (!get_oid_hex(arg, &oid)) {
				struct commit *commit;
				oidset_insert(common, &oid);
				commit = lookup_commit(the_repository, &oid);
				negotiator->ack(negotiator, commit);
			}
			continue;
		}

		if (!strcmp(reader->line, "ready")) {
			received_ready = 1;
			continue;
		}

		die(_("unexpected acknowledgment line: '%s'"), reader->line);
	}

	if (reader->status != PACKET_READ_FLUSH &&
	    reader->status != PACKET_READ_DELIM)
		die(_("error processing acks: %d"), reader->status);

	/*
	 * If an "acknowledgments" section is sent, a packfile is sent if and
	 * only if "ready" was sent in this section. The other sections
	 * ("shallow-info" and "wanted-refs") are sent only if a packfile is
	 * sent. Therefore, a DELIM is expected if "ready" is sent, and a FLUSH
	 * otherwise.
	 */
	if (received_ready && reader->status != PACKET_READ_DELIM)
		die(_("expected packfile to be sent after 'ready'"));
	if (!received_ready && reader->status != PACKET_READ_FLUSH)
		die(_("expected no other sections to be sent after no 'ready'"));

	/* return 0 if no common, 1 if there are common, or 2 if ready */
	return received_ready ? 2 : (received_ack ? 1 : 0);
}