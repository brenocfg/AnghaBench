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
struct tty {int dummy; } ;
struct thread {int dummy; } ;
struct rp_port {int /*<<< orphan*/  rp_channel; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ENOIOCTL ; 
#define  TIOCCBRK 129 
#define  TIOCSBRK 128 
 int /*<<< orphan*/  sClrBreak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sSendBreak (int /*<<< orphan*/ *) ; 
 struct rp_port* tty_softc (struct tty*) ; 

__attribute__((used)) static int
rpioctl(struct tty *tp, u_long cmd, caddr_t data, struct thread *td)
{
	struct rp_port	*rp;

	rp = tty_softc(tp);
	switch (cmd) {
	case TIOCSBRK:
		sSendBreak(&rp->rp_channel);
		return (0);
	case TIOCCBRK:
		sClrBreak(&rp->rp_channel);
		return (0);
	default:
		return ENOIOCTL;
	}
}