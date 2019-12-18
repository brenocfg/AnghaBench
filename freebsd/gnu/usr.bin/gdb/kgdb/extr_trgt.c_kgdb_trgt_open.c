#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread_info {int dummy; } ;
struct kthr {int /*<<< orphan*/  tid; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_t ;
struct TYPE_2__ {int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 struct thread_info* add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ ) ; 
 char* concat (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* curkthr ; 
 int /*<<< orphan*/  current_directory ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exec_bfd ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  frame_relative_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  get_selected_frame () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_thread_list () ; 
 int /*<<< orphan*/  kgdb_core_cleanup (char*) ; 
 int /*<<< orphan*/  kgdb_dmesg () ; 
 int /*<<< orphan*/  kgdb_resolve_symbol ; 
 struct kthr* kgdb_thr_init () ; 
 struct kthr* kgdb_thr_next (struct kthr*) ; 
 int /*<<< orphan*/  kgdb_trgt_ops ; 
 int /*<<< orphan*/  kld_init () ; 
 int /*<<< orphan*/ * kvm ; 
 int /*<<< orphan*/  kvm_err ; 
 int /*<<< orphan*/ * kvm_open2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/  (*) (char*),char*) ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_longname ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 char* tilde_expand (char*) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 
 char* vmcore ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_files ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static void
kgdb_trgt_open(char *filename, int from_tty)
{
	struct cleanup *old_chain;
	struct thread_info *ti;
	struct kthr *kt;
	kvm_t *nkvm;
	char *temp;
	int ontop;

	target_preopen (from_tty);
	if (!filename)
		error ("No vmcore file specified.");
	if (!exec_bfd)
		error ("Can't open a vmcore without a kernel");

	filename = tilde_expand (filename);
	if (filename[0] != '/') {
		temp = concat (current_directory, "/", filename, NULL);
		xfree(filename);
		filename = temp;
	}

	old_chain = make_cleanup (xfree, filename);

	nkvm = kvm_open2(bfd_get_filename(exec_bfd), filename,
	    write_files ? O_RDWR : O_RDONLY, kvm_err, kgdb_resolve_symbol);
	if (nkvm == NULL)
		error ("Failed to open vmcore: %s", kvm_err);

	/* Don't free the filename now and close any previous vmcore. */
	discard_cleanups(old_chain);
	unpush_target(&kgdb_trgt_ops);

	kvm = nkvm;
	vmcore = filename;
	old_chain = make_cleanup(kgdb_core_cleanup, NULL);

	ontop = !push_target (&kgdb_trgt_ops);
	discard_cleanups (old_chain);

	kgdb_dmesg();

	init_thread_list();
	kt = kgdb_thr_init();
	while (kt != NULL) {
		ti = add_thread(pid_to_ptid(kt->tid));
		kt = kgdb_thr_next(kt);
	}
	if (curkthr != 0)
		inferior_ptid = pid_to_ptid(curkthr->tid);

	if (ontop) {
		/* XXX: fetch registers? */
		kld_init();
		flush_cached_frames();
		select_frame (get_current_frame());
		print_stack_frame(get_selected_frame(),
		    frame_relative_level(get_selected_frame()), 1);
	} else
		warning(
	"you won't be able to access this vmcore until you terminate\n\
your %s; do ``info files''", target_longname);
}