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
struct thread {TYPE_2__* td_proc; } ;
struct priv_fw {int /*<<< orphan*/ * file; } ;
typedef  int /*<<< orphan*/ * linker_file_t ;
struct TYPE_4__ {TYPE_1__* p_fd; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fd_rdir; } ;

/* Variables and functions */
 struct thread* curthread ; 
 int /*<<< orphan*/  firmware_mtx ; 
 int linker_reference_module (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  linker_release_module (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct priv_fw* lookup (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  wakeup_one (char*) ; 

__attribute__((used)) static void
loadimage(void *arg, int npending)
{
	struct thread *td = curthread;
	char *imagename = arg;
	struct priv_fw *fp;
	linker_file_t result;
	int error;

	/* synchronize with the thread that dispatched us */
	mtx_lock(&firmware_mtx);
	mtx_unlock(&firmware_mtx);

	if (td->td_proc->p_fd->fd_rdir == NULL) {
		printf("%s: root not mounted yet, no way to load image\n",
		    imagename);
		goto done;
	}
	error = linker_reference_module(imagename, NULL, &result);
	if (error != 0) {
		printf("%s: could not load firmware image, error %d\n",
		    imagename, error);
		goto done;
	}

	mtx_lock(&firmware_mtx);
	fp = lookup(imagename, NULL);
	if (fp == NULL || fp->file != NULL) {
		mtx_unlock(&firmware_mtx);
		if (fp == NULL)
			printf("%s: firmware image loaded, "
			    "but did not register\n", imagename);
		(void) linker_release_module(imagename, NULL, NULL);
		goto done;
	}
	fp->file = result;	/* record the module identity */
	mtx_unlock(&firmware_mtx);
done:
	wakeup_one(imagename);		/* we're done */
}