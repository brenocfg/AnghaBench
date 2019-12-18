#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct filemon {int error; int /*<<< orphan*/  fname1; } ;
struct chdir_args {int /*<<< orphan*/  path; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int copyinstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* curproc ; 
 int /*<<< orphan*/  filemon_drop (struct filemon*) ; 
 int /*<<< orphan*/  filemon_output_event (struct filemon*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct filemon* filemon_proc_get (TYPE_1__*) ; 
 int sys_chdir (struct thread*,struct chdir_args*) ; 

__attribute__((used)) static int
filemon_wrapper_chdir(struct thread *td, struct chdir_args *uap)
{
	int error, ret;
	struct filemon *filemon;

	if ((ret = sys_chdir(td, uap)) == 0) {
		if ((filemon = filemon_proc_get(curproc)) != NULL) {
			if ((error = copyinstr(uap->path, filemon->fname1,
			    sizeof(filemon->fname1), NULL)) != 0) {
				filemon->error = error;
				goto copyfail;
			}

			filemon_output_event(filemon, "C %d %s\n",
			    curproc->p_pid, filemon->fname1);
copyfail:
			filemon_drop(filemon);
		}
	}

	return (ret);
}