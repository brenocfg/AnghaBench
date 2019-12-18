#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct thread {TYPE_1__* td_proc; } ;
struct isc_softc {int dummy; } ;
struct cdev {TYPE_2__* si_drv2; struct isc_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  iscsi_cam_t ;
struct TYPE_7__ {int signal; int /*<<< orphan*/ * soc; TYPE_1__* proc; int /*<<< orphan*/  oid; int /*<<< orphan*/  clist; } ;
typedef  TYPE_2__ isc_session_t ;
typedef  int /*<<< orphan*/  isc_opt_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int EINVAL ; 
 int ENOIOCTL ; 
 int ENOTCONN ; 
 int ENXIO ; 
#define  ISCSIGETCAM 138 
#define  ISCSIPING 137 
#define  ISCSIRECV 136 
#define  ISCSIRESTART 135 
#define  ISCSISEND 134 
#define  ISCSISETOPT 133 
#define  ISCSISETSES 132 
#define  ISCSISETSOC 131 
#define  ISCSISIGNAL 130 
#define  ISCSISTART 129 
#define  ISCSISTOP 128 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int _SIG_MAXSIG ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ dev2unit (struct cdev*) ; 
 int i_create_session (struct cdev*,int*) ; 
 int i_fullfeature (struct cdev*,int) ; 
 int i_ping (struct cdev*) ; 
 int i_recv (struct cdev*,scalar_t__,struct thread*) ; 
 int i_send (struct cdev*,scalar_t__,struct thread*) ; 
 int i_setopt (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int i_setsoc (TYPE_2__*,int /*<<< orphan*/ ,struct thread*) ; 
 int ic_getCamVals (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ max_sessions ; 
 int /*<<< orphan*/  sdebug (int,char*,scalar_t__,int) ; 

__attribute__((used)) static int
iscsi_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int mode, struct thread *td)
{
     struct isc_softc	*sc;
     isc_session_t	*sp;
     isc_opt_t		*opt;
     int		error;

     debug_called(8);

     error = 0;
     if(dev2unit(dev) == max_sessions) {
	  /*
	   | non Session commands
	   */
	  sc = dev->si_drv1;
	  if(sc == NULL)
	       return ENXIO;

	  switch(cmd) {
	  case ISCSISETSES:
	       error = i_create_session(dev, (int *)arg);
	       if(error == 0)
		    break;

	  default:
	       error = ENXIO;
	  }
	  return error;
     }
     /*
      | session commands
      */
     sp = dev->si_drv2;
     if(sp == NULL)
	  return ENXIO;

     sdebug(6, "dev=%d cmd=%d", dev2unit(dev), (int)(cmd & 0xff));

     switch(cmd) {
     case ISCSISETSOC:
	  error = i_setsoc(sp, *(u_int *)arg, td);
	  break;

     case ISCSISETOPT:
	  opt = (isc_opt_t *)arg;
	  error = i_setopt(sp, opt);
	  break;

     case ISCSISEND:
	  error = i_send(dev, arg, td);
	  break;

     case ISCSIRECV:
	  error = i_recv(dev, arg, td);
	  break;

     case ISCSIPING:
	  error = i_ping(dev);
	  break;

     case ISCSISTART:
	  error = sp->soc == NULL? ENOTCONN: i_fullfeature(dev, 1);
	  if(error == 0) {
	       sp->proc = td->td_proc;
	       SYSCTL_ADD_INT(&sp->clist, SYSCTL_CHILDREN(sp->oid),
			       OID_AUTO, "pid", CTLFLAG_RD,
			       &sp->proc->p_pid, sizeof(pid_t), "control process id");
	  }
	  break;

     case ISCSIRESTART:
	  error = sp->soc == NULL? ENOTCONN: i_fullfeature(dev, 2);
	  break;

     case ISCSISTOP:
	  error = i_fullfeature(dev, 0);
	  break;
	  
     case ISCSISIGNAL: {
	  int sig = *(int *)arg;

	  if(sig < 0 || sig > _SIG_MAXSIG)
	       error = EINVAL;
	  else
		sp->signal = sig;
	  break;
     }

     case ISCSIGETCAM: {
	  iscsi_cam_t *cp = (iscsi_cam_t *)arg;

	  error = ic_getCamVals(sp, cp);
	  break;
     }

     default:
	  error = ENOIOCTL;
     }

     return error;
}