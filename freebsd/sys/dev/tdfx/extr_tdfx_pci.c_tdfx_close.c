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
struct thread {TYPE_1__* td_proc; } ;
struct tdfx_softc {scalar_t__ busy; } ;
struct cdev {struct tdfx_softc* si_drv1; } ;
struct TYPE_2__ {int p_pid; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int 
tdfx_close(struct cdev *dev, int fflag, int devtype, struct thread *td) 
{
	/* 
	 *	The close cdev method handles close(2) calls to /dev/3dfx[n] 
	 * We'll always want to close the device when it's called.
	 */
	struct tdfx_softc *tdfx_info = dev->si_drv1;
	if(tdfx_info->busy == 0) return EBADF;
	tdfx_info->busy = 0;
#ifdef	DEBUG
	printf("Closed by #%d\n", td->td_proc->p_pid);
#endif
	return 0;
}