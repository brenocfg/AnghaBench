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
struct filemon {int error; int /*<<< orphan*/  fname2; int /*<<< orphan*/  fname1; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int copyinstr (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* curproc ; 
 int /*<<< orphan*/  filemon_drop (struct filemon*) ; 
 int /*<<< orphan*/  filemon_output_event (struct filemon*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct filemon* filemon_proc_get (TYPE_1__*) ; 

__attribute__((used)) static void
_filemon_wrapper_link(struct thread *td, const char *upath1,
    const char *upath2)
{
	struct filemon *filemon;
	int error;

	if ((filemon = filemon_proc_get(curproc)) != NULL) {
		if (((error = copyinstr(upath1, filemon->fname1,
		     sizeof(filemon->fname1), NULL)) != 0) ||
		    ((error = copyinstr(upath2, filemon->fname2,
		     sizeof(filemon->fname2), NULL)) != 0)) {
			filemon->error = error;
			goto copyfail;
		}

		filemon_output_event(filemon, "L %d '%s' '%s'\n",
		    curproc->p_pid, filemon->fname1, filemon->fname2);
copyfail:
		filemon_drop(filemon);
	}
}