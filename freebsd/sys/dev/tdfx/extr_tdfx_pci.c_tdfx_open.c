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
 int EBUSY ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
tdfx_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	/* 
	 *	The open cdev method handles open(2) calls to /dev/3dfx[n] 
	 * We can pretty much allow any opening of the device.
	 */
	struct tdfx_softc *tdfx_info = dev->si_drv1;
	if(tdfx_info->busy != 0) return EBUSY;
#ifdef	DEBUG
	printf("3dfx: Opened by #%d\n", td->td_proc->p_pid);
#endif
	/* Set the driver as busy */
	tdfx_info->busy++;
	return 0;
}