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
struct transport {struct helper_data* data; } ;
struct strbuf {char* buf; } ;
struct ref {char* name; struct ref* next; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  status; int /*<<< orphan*/  symref; } ;
struct helper_data {int get_refs_list_called; scalar_t__ push; } ;
struct child_process {int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_STATUS_UPTODATE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct ref* alloc_ref (char*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct child_process* get_helper (struct transport*) ; 
 int /*<<< orphan*/  get_oid_hex (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ has_attribute (char*,char*) ; 
 scalar_t__ read_ref (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ recvline (struct helper_data*,struct strbuf*) ; 
 int /*<<< orphan*/  resolve_remote_symref (struct ref*,struct ref*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  write_str_in_full (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static struct ref *get_refs_list_using_list(struct transport *transport,
					    int for_push)
{
	struct helper_data *data = transport->data;
	struct child_process *helper;
	struct ref *ret = NULL;
	struct ref **tail = &ret;
	struct ref *posn;
	struct strbuf buf = STRBUF_INIT;

	data->get_refs_list_called = 1;
	helper = get_helper(transport);

	if (data->push && for_push)
		write_str_in_full(helper->in, "list for-push\n");
	else
		write_str_in_full(helper->in, "list\n");

	while (1) {
		char *eov, *eon;
		if (recvline(data, &buf))
			exit(128);

		if (!*buf.buf)
			break;

		eov = strchr(buf.buf, ' ');
		if (!eov)
			die(_("malformed response in ref list: %s"), buf.buf);
		eon = strchr(eov + 1, ' ');
		*eov = '\0';
		if (eon)
			*eon = '\0';
		*tail = alloc_ref(eov + 1);
		if (buf.buf[0] == '@')
			(*tail)->symref = xstrdup(buf.buf + 1);
		else if (buf.buf[0] != '?')
			get_oid_hex(buf.buf, &(*tail)->old_oid);
		if (eon) {
			if (has_attribute(eon + 1, "unchanged")) {
				(*tail)->status |= REF_STATUS_UPTODATE;
				if (read_ref((*tail)->name, &(*tail)->old_oid) < 0)
					die(_("could not read ref %s"),
					    (*tail)->name);
			}
		}
		tail = &((*tail)->next);
	}
	if (debug)
		fprintf(stderr, "Debug: Read ref listing.\n");
	strbuf_release(&buf);

	for (posn = ret; posn; posn = posn->next)
		resolve_remote_symref(posn, ret);

	return ret;
}