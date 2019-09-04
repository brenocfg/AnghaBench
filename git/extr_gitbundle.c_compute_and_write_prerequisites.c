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
struct strbuf {scalar_t__ len; char* buf; } ;
struct rev_info {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int /*<<< orphan*/  flags; } ;
struct child_process {int out; int git_cmd; int /*<<< orphan*/  args; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  SHOWN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UNINTERESTING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  get_oid_hex (char*,struct object_id*) ; 
 struct object* parse_object_or_die (struct object_id*,char*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 scalar_t__ strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  write_or_die (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * xfdopen (int,char*) ; 

__attribute__((used)) static int compute_and_write_prerequisites(int bundle_fd,
					   struct rev_info *revs,
					   int argc, const char **argv)
{
	struct child_process rls = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	FILE *rls_fout;
	int i;

	argv_array_pushl(&rls.args,
			 "rev-list", "--boundary", "--pretty=oneline",
			 NULL);
	for (i = 1; i < argc; i++)
		argv_array_push(&rls.args, argv[i]);
	rls.out = -1;
	rls.git_cmd = 1;
	if (start_command(&rls))
		return -1;
	rls_fout = xfdopen(rls.out, "r");
	while (strbuf_getwholeline(&buf, rls_fout, '\n') != EOF) {
		struct object_id oid;
		if (buf.len > 0 && buf.buf[0] == '-') {
			write_or_die(bundle_fd, buf.buf, buf.len);
			if (!get_oid_hex(buf.buf + 1, &oid)) {
				struct object *object = parse_object_or_die(&oid,
									    buf.buf);
				object->flags |= UNINTERESTING;
				add_pending_object(revs, object, buf.buf);
			}
		} else if (!get_oid_hex(buf.buf, &oid)) {
			struct object *object = parse_object_or_die(&oid,
								    buf.buf);
			object->flags |= SHOWN;
		}
	}
	strbuf_release(&buf);
	fclose(rls_fout);
	if (finish_command(&rls))
		return error(_("rev-list died"));
	return 0;
}