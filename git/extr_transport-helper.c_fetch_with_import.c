#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct transport {struct helper_data* data; } ;
struct strbuf {int dummy; } ;
struct ref {int status; char* symref; char* name; int /*<<< orphan*/  old_oid; } ;
struct TYPE_4__ {scalar_t__ nr; } ;
struct helper_data {TYPE_2__ rs; TYPE_1__* helper; } ;
struct child_process {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int REF_STATUS_UPTODATE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apply_refspecs (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_helper (struct transport*) ; 
 scalar_t__ get_importer (struct transport*,struct child_process*) ; 
 scalar_t__ read_ref (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendline (struct helper_data*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  write_constant (int /*<<< orphan*/ ,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int fetch_with_import(struct transport *transport,
			     int nr_heads, struct ref **to_fetch)
{
	struct child_process fastimport;
	struct helper_data *data = transport->data;
	int i;
	struct ref *posn;
	struct strbuf buf = STRBUF_INIT;

	get_helper(transport);

	if (get_importer(transport, &fastimport))
		die(_("couldn't run fast-import"));

	for (i = 0; i < nr_heads; i++) {
		posn = to_fetch[i];
		if (posn->status & REF_STATUS_UPTODATE)
			continue;

		strbuf_addf(&buf, "import %s\n",
			    posn->symref ? posn->symref : posn->name);
		sendline(data, &buf);
		strbuf_reset(&buf);
	}

	write_constant(data->helper->in, "\n");
	/*
	 * remote-helpers that advertise the bidi-import capability are required to
	 * buffer the complete batch of import commands until this newline before
	 * sending data to fast-import.
	 * These helpers read back data from fast-import on their stdin, which could
	 * be mixed with import commands, otherwise.
	 */

	if (finish_command(&fastimport))
		die(_("error while running fast-import"));

	/*
	 * The fast-import stream of a remote helper that advertises
	 * the "refspec" capability writes to the refs named after the
	 * right hand side of the first refspec matching each ref we
	 * were fetching.
	 *
	 * (If no "refspec" capability was specified, for historical
	 * reasons we default to the equivalent of *:*.)
	 *
	 * Store the result in to_fetch[i].old_sha1.  Callers such
	 * as "git fetch" can use the value to write feedback to the
	 * terminal, populate FETCH_HEAD, and determine what new value
	 * should be written to peer_ref if the update is a
	 * fast-forward or this is a forced update.
	 */
	for (i = 0; i < nr_heads; i++) {
		char *private, *name;
		posn = to_fetch[i];
		if (posn->status & REF_STATUS_UPTODATE)
			continue;
		name = posn->symref ? posn->symref : posn->name;
		if (data->rs.nr)
			private = apply_refspecs(&data->rs, name);
		else
			private = xstrdup(name);
		if (private) {
			if (read_ref(private, &posn->old_oid) < 0)
				die(_("could not read ref %s"), private);
			free(private);
		}
	}
	strbuf_release(&buf);
	return 0;
}