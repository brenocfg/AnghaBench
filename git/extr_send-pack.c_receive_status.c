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
struct ref {scalar_t__ status; struct ref* next; int /*<<< orphan*/  remote_status; } ;
struct packet_reader {char* line; } ;

/* Variables and functions */
 scalar_t__ PACKET_READ_NORMAL ; 
 scalar_t__ REF_STATUS_EXPECTING_REPORT ; 
 scalar_t__ REF_STATUS_OK ; 
 scalar_t__ REF_STATUS_REMOTE_REJECT ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 struct ref* find_ref_by_name (struct ref*,char const*) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 int receive_unpack_status (struct packet_reader*) ; 
 int /*<<< orphan*/  starts_with (char*,char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 
 int /*<<< orphan*/  xstrdup_or_null (char*) ; 

__attribute__((used)) static int receive_status(struct packet_reader *reader, struct ref *refs)
{
	struct ref *hint;
	int ret;

	hint = NULL;
	ret = receive_unpack_status(reader);
	while (1) {
		const char *refname;
		char *msg;
		if (packet_reader_read(reader) != PACKET_READ_NORMAL)
			break;
		if (!starts_with(reader->line, "ok ") && !starts_with(reader->line, "ng ")) {
			error("invalid ref status from remote: %s", reader->line);
			ret = -1;
			break;
		}

		refname = reader->line + 3;
		msg = strchr(refname, ' ');
		if (msg)
			*msg++ = '\0';

		/* first try searching at our hint, falling back to all refs */
		if (hint)
			hint = find_ref_by_name(hint, refname);
		if (!hint)
			hint = find_ref_by_name(refs, refname);
		if (!hint) {
			warning("remote reported status on unknown ref: %s",
					refname);
			continue;
		}
		if (hint->status != REF_STATUS_EXPECTING_REPORT) {
			warning("remote reported status on unexpected ref: %s",
					refname);
			continue;
		}

		if (reader->line[0] == 'o' && reader->line[1] == 'k')
			hint->status = REF_STATUS_OK;
		else {
			hint->status = REF_STATUS_REMOTE_REJECT;
			ret = -1;
		}
		hint->remote_status = xstrdup_or_null(msg);
		/* start our next search from the next ref */
		hint = hint->next;
	}
	return ret;
}