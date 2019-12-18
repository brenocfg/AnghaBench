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
struct transport {scalar_t__ pack_lockfile; TYPE_1__* smart_options; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct packed_git {int dummy; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct child_process {int git_cmd; int in; int no_stdout; int err; int /*<<< orphan*/  no_stderr; int /*<<< orphan*/  env; int /*<<< orphan*/  args; } ;
struct check_connected_options {int err_fd; char* shallow_file; int /*<<< orphan*/  quiet; int /*<<< orphan*/  env; scalar_t__ progress; int /*<<< orphan*/  is_deepening_fetch; scalar_t__ check_refs_only; struct transport* transport; } ;
typedef  scalar_t__ (* oid_iterate_fn ) (void*,struct object_id*) ;
struct TYPE_4__ {unsigned int hexsz; } ;
struct TYPE_3__ {scalar_t__ self_contained_and_connected; } ;

/* Variables and functions */
 struct check_connected_options CHECK_CONNECTED_INIT ; 
 struct child_process CHILD_PROCESS_INIT ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct packed_git* add_packed_git (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ close (int) ; 
 scalar_t__ errno ; 
 int error (int /*<<< orphan*/ ) ; 
 int error_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ find_pack_entry_one (int /*<<< orphan*/ ,struct packed_git*) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 scalar_t__ has_promisor_remote () ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  repo_has_object_file (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strip_suffix (scalar_t__,char*,size_t*) ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ write_in_full (int,char*,unsigned int const) ; 

int check_connected(oid_iterate_fn fn, void *cb_data,
		    struct check_connected_options *opt)
{
	struct child_process rev_list = CHILD_PROCESS_INIT;
	struct check_connected_options defaults = CHECK_CONNECTED_INIT;
	char commit[GIT_MAX_HEXSZ + 1];
	struct object_id oid;
	int err = 0;
	struct packed_git *new_pack = NULL;
	struct transport *transport;
	size_t base_len;
	const unsigned hexsz = the_hash_algo->hexsz;

	if (!opt)
		opt = &defaults;
	transport = opt->transport;

	if (fn(cb_data, &oid)) {
		if (opt->err_fd)
			close(opt->err_fd);
		return err;
	}

	if (transport && transport->smart_options &&
	    transport->smart_options->self_contained_and_connected &&
	    transport->pack_lockfile &&
	    strip_suffix(transport->pack_lockfile, ".keep", &base_len)) {
		struct strbuf idx_file = STRBUF_INIT;
		strbuf_add(&idx_file, transport->pack_lockfile, base_len);
		strbuf_addstr(&idx_file, ".idx");
		new_pack = add_packed_git(idx_file.buf, idx_file.len, 1);
		strbuf_release(&idx_file);
	}

	if (opt->check_refs_only) {
		/*
		 * For partial clones, we don't want to have to do a regular
		 * connectivity check because we have to enumerate and exclude
		 * all promisor objects (slow), and then the connectivity check
		 * itself becomes a no-op because in a partial clone every
		 * object is a promisor object. Instead, just make sure we
		 * received the objects pointed to by each wanted ref.
		 */
		do {
			if (!repo_has_object_file(the_repository, &oid))
				return 1;
		} while (!fn(cb_data, &oid));
		return 0;
	}

	if (opt->shallow_file) {
		argv_array_push(&rev_list.args, "--shallow-file");
		argv_array_push(&rev_list.args, opt->shallow_file);
	}
	argv_array_push(&rev_list.args,"rev-list");
	argv_array_push(&rev_list.args, "--objects");
	argv_array_push(&rev_list.args, "--stdin");
	if (has_promisor_remote())
		argv_array_push(&rev_list.args, "--exclude-promisor-objects");
	if (!opt->is_deepening_fetch) {
		argv_array_push(&rev_list.args, "--not");
		argv_array_push(&rev_list.args, "--all");
	}
	argv_array_push(&rev_list.args, "--quiet");
	argv_array_push(&rev_list.args, "--alternate-refs");
	if (opt->progress)
		argv_array_pushf(&rev_list.args, "--progress=%s",
				 _("Checking connectivity"));

	rev_list.git_cmd = 1;
	rev_list.env = opt->env;
	rev_list.in = -1;
	rev_list.no_stdout = 1;
	if (opt->err_fd)
		rev_list.err = opt->err_fd;
	else
		rev_list.no_stderr = opt->quiet;

	if (start_command(&rev_list))
		return error(_("Could not run 'git rev-list'"));

	sigchain_push(SIGPIPE, SIG_IGN);

	commit[hexsz] = '\n';
	do {
		/*
		 * If index-pack already checked that:
		 * - there are no dangling pointers in the new pack
		 * - the pack is self contained
		 * Then if the updated ref is in the new pack, then we
		 * are sure the ref is good and not sending it to
		 * rev-list for verification.
		 */
		if (new_pack && find_pack_entry_one(oid.hash, new_pack))
			continue;

		memcpy(commit, oid_to_hex(&oid), hexsz);
		if (write_in_full(rev_list.in, commit, hexsz + 1) < 0) {
			if (errno != EPIPE && errno != EINVAL)
				error_errno(_("failed write to rev-list"));
			err = -1;
			break;
		}
	} while (!fn(cb_data, &oid));

	if (close(rev_list.in))
		err = error_errno(_("failed to close rev-list's stdin"));

	sigchain_pop(SIGPIPE);
	return finish_command(&rev_list) || err;
}