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
struct send_pack_args {scalar_t__ stateless_rpc; scalar_t__ progress; scalar_t__ quiet; scalar_t__ use_ofs_delta; scalar_t__ use_thin_pack; } ;
struct ref {struct ref* next; int /*<<< orphan*/  new_oid; int /*<<< orphan*/  old_oid; } ;
struct oid_array {int nr; int /*<<< orphan*/ * oid; } ;
struct child_process {int in; int out; int git_cmd; int /*<<< orphan*/  args; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  LARGE_PACKET_MAX ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feed_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int finish_command (struct child_process*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 scalar_t__ is_repository_shallow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sideband (int,int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/ * xfdopen (int,char*) ; 
 char* xmalloc (int /*<<< orphan*/ ) ; 
 scalar_t__ xread (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pack_objects(int fd, struct ref *refs, struct oid_array *extra, struct send_pack_args *args)
{
	/*
	 * The child becomes pack-objects --revs; we feed
	 * the revision parameters to it via its stdin and
	 * let its stdout go back to the other end.
	 */
	struct child_process po = CHILD_PROCESS_INIT;
	FILE *po_in;
	int i;
	int rc;

	argv_array_push(&po.args, "pack-objects");
	argv_array_push(&po.args, "--all-progress-implied");
	argv_array_push(&po.args, "--revs");
	argv_array_push(&po.args, "--stdout");
	if (args->use_thin_pack)
		argv_array_push(&po.args, "--thin");
	if (args->use_ofs_delta)
		argv_array_push(&po.args, "--delta-base-offset");
	if (args->quiet || !args->progress)
		argv_array_push(&po.args, "-q");
	if (args->progress)
		argv_array_push(&po.args, "--progress");
	if (is_repository_shallow(the_repository))
		argv_array_push(&po.args, "--shallow");
	po.in = -1;
	po.out = args->stateless_rpc ? -1 : fd;
	po.git_cmd = 1;
	if (start_command(&po))
		die_errno("git pack-objects failed");

	/*
	 * We feed the pack-objects we just spawned with revision
	 * parameters by writing to the pipe.
	 */
	po_in = xfdopen(po.in, "w");
	for (i = 0; i < extra->nr; i++)
		feed_object(&extra->oid[i], po_in, 1);

	while (refs) {
		if (!is_null_oid(&refs->old_oid))
			feed_object(&refs->old_oid, po_in, 1);
		if (!is_null_oid(&refs->new_oid))
			feed_object(&refs->new_oid, po_in, 0);
		refs = refs->next;
	}

	fflush(po_in);
	if (ferror(po_in))
		die_errno("error writing to pack-objects");
	fclose(po_in);

	if (args->stateless_rpc) {
		char *buf = xmalloc(LARGE_PACKET_MAX);
		while (1) {
			ssize_t n = xread(po.out, buf, LARGE_PACKET_MAX);
			if (n <= 0)
				break;
			send_sideband(fd, -1, buf, n, LARGE_PACKET_MAX);
		}
		free(buf);
		close(po.out);
		po.out = -1;
	}

	rc = finish_command(&po);
	if (rc) {
		/*
		 * For a normal non-zero exit, we assume pack-objects wrote
		 * something useful to stderr. For death by signal, though,
		 * we should mention it to the user. The exception is SIGPIPE
		 * (141), because that's a normal occurrence if the remote end
		 * hangs up (and we'll report that by trying to read the unpack
		 * status).
		 */
		if (rc > 128 && rc != 141)
			error("pack-objects died of signal %d", rc - 128);
		return -1;
	}
	return 0;
}