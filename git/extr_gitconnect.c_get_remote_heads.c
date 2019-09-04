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
struct ref {int dummy; } ;
struct packet_reader {int pktlen; int /*<<< orphan*/  line; } ;
struct oid_array {int dummy; } ;
typedef  enum get_remote_heads_state { ____Placeholder_get_remote_heads_state } get_remote_heads_state ;

/* Variables and functions */
#define  EXPECTING_DONE 135 
#define  EXPECTING_FIRST_REF 134 
#define  EXPECTING_REF 133 
#define  EXPECTING_SHALLOW 132 
#define  PACKET_READ_DELIM 131 
#define  PACKET_READ_EOF 130 
#define  PACKET_READ_FLUSH 129 
#define  PACKET_READ_NORMAL 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  annotate_refs_with_symref_info (struct ref*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  die_initial_contact (int) ; 
 int packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  process_capabilities (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  process_dummy_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_ref (int /*<<< orphan*/ ,int,struct ref***,unsigned int,struct oid_array*) ; 
 int /*<<< orphan*/  process_shallow (int /*<<< orphan*/ ,int,struct oid_array*) ; 

struct ref **get_remote_heads(struct packet_reader *reader,
			      struct ref **list, unsigned int flags,
			      struct oid_array *extra_have,
			      struct oid_array *shallow_points)
{
	struct ref **orig_list = list;
	int len = 0;
	enum get_remote_heads_state state = EXPECTING_FIRST_REF;

	*list = NULL;

	while (state != EXPECTING_DONE) {
		switch (packet_reader_read(reader)) {
		case PACKET_READ_EOF:
			die_initial_contact(1);
		case PACKET_READ_NORMAL:
			len = reader->pktlen;
			break;
		case PACKET_READ_FLUSH:
			state = EXPECTING_DONE;
			break;
		case PACKET_READ_DELIM:
			die(_("invalid packet"));
		}

		switch (state) {
		case EXPECTING_FIRST_REF:
			process_capabilities(reader->line, &len);
			if (process_dummy_ref(reader->line)) {
				state = EXPECTING_SHALLOW;
				break;
			}
			state = EXPECTING_REF;
			/* fallthrough */
		case EXPECTING_REF:
			if (process_ref(reader->line, len, &list, flags, extra_have))
				break;
			state = EXPECTING_SHALLOW;
			/* fallthrough */
		case EXPECTING_SHALLOW:
			if (process_shallow(reader->line, len, shallow_points))
				break;
			die(_("protocol error: unexpected '%s'"), reader->line);
		case EXPECTING_DONE:
			break;
		}
	}

	annotate_refs_with_symref_info(*orig_list);

	return list;
}