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
struct string_list {int dummy; } ;
struct strbuf {char* buf; } ;
struct ref {char* name; TYPE_1__* peer_ref; int /*<<< orphan*/  deletion; int /*<<< orphan*/  old_oid; struct ref* next; } ;
struct object_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr; } ;
struct helper_data {char* export_marks; TYPE_2__ rs; int /*<<< orphan*/  name; } ;
struct child_process {int /*<<< orphan*/  in; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int TRANSPORT_PUSH_FORCE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apply_refspecs (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_exporter (struct transport*,struct child_process*,struct string_list*) ; 
 struct child_process* get_helper (struct transport*) ; 
 int /*<<< orphan*/  get_oid (char*,struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 scalar_t__ push_update_refs_status (struct helper_data*,struct ref*,int) ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 char* resolve_ref_unsafe (char*,int /*<<< orphan*/ ,struct object_id*,int*) ; 
 int /*<<< orphan*/  set_common_push_options (struct transport*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ set_helper_option (struct transport*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char*) ; 
 int /*<<< orphan*/  string_list_append_nodup (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_constant (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int push_refs_with_export(struct transport *transport,
		struct ref *remote_refs, int flags)
{
	struct ref *ref;
	struct child_process *helper, exporter;
	struct helper_data *data = transport->data;
	struct string_list revlist_args = STRING_LIST_INIT_DUP;
	struct strbuf buf = STRBUF_INIT;

	if (!data->rs.nr)
		die(_("remote-helper doesn't support push; refspec needed"));

	set_common_push_options(transport, data->name, flags);
	if (flags & TRANSPORT_PUSH_FORCE) {
		if (set_helper_option(transport, "force", "true") != 0)
			warning(_("helper %s does not support 'force'"), data->name);
	}

	helper = get_helper(transport);

	write_constant(helper->in, "export\n");

	for (ref = remote_refs; ref; ref = ref->next) {
		char *private;
		struct object_id oid;

		private = apply_refspecs(&data->rs, ref->name);
		if (private && !get_oid(private, &oid)) {
			strbuf_addf(&buf, "^%s", private);
			string_list_append_nodup(&revlist_args,
						 strbuf_detach(&buf, NULL));
			oidcpy(&ref->old_oid, &oid);
		}
		free(private);

		if (ref->peer_ref) {
			if (strcmp(ref->name, ref->peer_ref->name)) {
				if (!ref->deletion) {
					const char *name;
					int flag;

					/* Follow symbolic refs (mainly for HEAD). */
					name = resolve_ref_unsafe(ref->peer_ref->name,
								  RESOLVE_REF_READING,
								  &oid, &flag);
					if (!name || !(flag & REF_ISSYMREF))
						name = ref->peer_ref->name;

					strbuf_addf(&buf, "%s:%s", name, ref->name);
				} else
					strbuf_addf(&buf, ":%s", ref->name);

				string_list_append(&revlist_args, "--refspec");
				string_list_append(&revlist_args, buf.buf);
				strbuf_release(&buf);
			}
			if (!ref->deletion)
				string_list_append(&revlist_args, ref->peer_ref->name);
		}
	}

	if (get_exporter(transport, &exporter, &revlist_args))
		die(_("couldn't run fast-export"));

	string_list_clear(&revlist_args, 1);

	if (finish_command(&exporter))
		die(_("error while running fast-export"));
	if (push_update_refs_status(data, remote_refs, flags))
		return 1;

	if (data->export_marks) {
		strbuf_addf(&buf, "%s.tmp", data->export_marks);
		rename(buf.buf, data->export_marks);
		strbuf_release(&buf);
	}

	return 0;
}