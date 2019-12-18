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
typedef  scalar_t__ u_long ;
typedef  int u_int32_t ;
struct thread {int* td_retval; TYPE_1__* td_proc; } ;
struct tdfx_pio_data {int dummy; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int p_pid; } ;

/* Variables and functions */
 int ENXIO ; 
 int _IOC_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  tdfx_do_pio (scalar_t__,struct tdfx_pio_data*) ; 
 int tdfx_do_query (scalar_t__,struct tdfx_pio_data*) ; 

__attribute__((used)) static int
tdfx_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flag, struct thread *td)
{
	int retval = 0;
	struct tdfx_pio_data *piod = (struct tdfx_pio_data*)data;
#ifdef	DEBUG
	printf("IOCTL'd by #%d, cmd: 0x%x, data: %p\n", td->td_proc->p_pid, (u_int32_t)cmd,
			piod);
#endif
	switch(_IOC_TYPE(cmd)) {
		/* Return the real error if negative, or simply stick the valid return
		 * in td->td_retval */
	case 0x33:
			/* The '3'(0x33) type IOCTL is for querying the installed cards */
			if((retval = tdfx_do_query(cmd, piod)) > 0) td->td_retval[0] = retval;
			else return -retval;
			break;
		case 0:
			/* The 0 type IOCTL is for programmed I/O methods */
			if((tdfx_do_pio(cmd, piod)) > 0) td->td_retval[0] = retval;
			else return -retval;
			break;
		default:
			/* Technically, we won't reach this from linux emu, but when glide
			 * finally gets ported, watch out! */
#ifdef DEBUG
			printf("Bad IOCTL from #%d\n", td->td_proc->p_pid);
#endif
			return ENXIO;
	}

	return 0;
}