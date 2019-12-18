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
typedef  int u_long ;
struct thread {int dummy; } ;
struct iscsi_softc {int dummy; } ;
struct iscsi_session_remove {int dummy; } ;
struct iscsi_session_modify {int dummy; } ;
struct iscsi_session_list {int dummy; } ;
struct iscsi_session_add {int dummy; } ;
struct iscsi_daemon_send {int dummy; } ;
struct iscsi_daemon_request {int dummy; } ;
struct iscsi_daemon_receive {int dummy; } ;
struct iscsi_daemon_handoff {int dummy; } ;
struct iscsi_daemon_fail {int dummy; } ;
struct iscsi_daemon_connect {int dummy; } ;
struct cdev {struct iscsi_softc* si_drv1; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  ISCSIDCONNECT 137 
#define  ISCSIDFAIL 136 
#define  ISCSIDHANDOFF 135 
#define  ISCSIDRECEIVE 134 
#define  ISCSIDSEND 133 
#define  ISCSIDWAIT 132 
#define  ISCSISADD 131 
#define  ISCSISLIST 130 
#define  ISCSISMODIFY 129 
#define  ISCSISREMOVE 128 
 int iscsi_ioctl_daemon_connect (struct iscsi_softc*,struct iscsi_daemon_connect*) ; 
 int iscsi_ioctl_daemon_fail (struct iscsi_softc*,struct iscsi_daemon_fail*) ; 
 int iscsi_ioctl_daemon_handoff (struct iscsi_softc*,struct iscsi_daemon_handoff*) ; 
 int iscsi_ioctl_daemon_receive (struct iscsi_softc*,struct iscsi_daemon_receive*) ; 
 int iscsi_ioctl_daemon_send (struct iscsi_softc*,struct iscsi_daemon_send*) ; 
 int iscsi_ioctl_daemon_wait (struct iscsi_softc*,struct iscsi_daemon_request*) ; 
 int iscsi_ioctl_session_add (struct iscsi_softc*,struct iscsi_session_add*) ; 
 int iscsi_ioctl_session_list (struct iscsi_softc*,struct iscsi_session_list*) ; 
 int iscsi_ioctl_session_modify (struct iscsi_softc*,struct iscsi_session_modify*) ; 
 int iscsi_ioctl_session_remove (struct iscsi_softc*,struct iscsi_session_remove*) ; 

__attribute__((used)) static int
iscsi_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int mode,
    struct thread *td)
{
	struct iscsi_softc *sc;

	sc = dev->si_drv1;

	switch (cmd) {
	case ISCSIDWAIT:
		return (iscsi_ioctl_daemon_wait(sc,
		    (struct iscsi_daemon_request *)arg));
	case ISCSIDHANDOFF:
		return (iscsi_ioctl_daemon_handoff(sc,
		    (struct iscsi_daemon_handoff *)arg));
	case ISCSIDFAIL:
		return (iscsi_ioctl_daemon_fail(sc,
		    (struct iscsi_daemon_fail *)arg));
#ifdef ICL_KERNEL_PROXY
	case ISCSIDCONNECT:
		return (iscsi_ioctl_daemon_connect(sc,
		    (struct iscsi_daemon_connect *)arg));
	case ISCSIDSEND:
		return (iscsi_ioctl_daemon_send(sc,
		    (struct iscsi_daemon_send *)arg));
	case ISCSIDRECEIVE:
		return (iscsi_ioctl_daemon_receive(sc,
		    (struct iscsi_daemon_receive *)arg));
#endif /* ICL_KERNEL_PROXY */
	case ISCSISADD:
		return (iscsi_ioctl_session_add(sc,
		    (struct iscsi_session_add *)arg));
	case ISCSISREMOVE:
		return (iscsi_ioctl_session_remove(sc,
		    (struct iscsi_session_remove *)arg));
	case ISCSISLIST:
		return (iscsi_ioctl_session_list(sc,
		    (struct iscsi_session_list *)arg));
	case ISCSISMODIFY:
		return (iscsi_ioctl_session_modify(sc,
		    (struct iscsi_session_modify *)arg));
	default:
		return (EINVAL);
	}
}