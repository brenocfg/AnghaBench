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
struct TYPE_4__ {int /*<<< orphan*/  sb_cc; } ;
struct TYPE_3__ {int /*<<< orphan*/  sb_cc; } ;
struct xsocket {TYPE_2__ so_snd; TYPE_1__ so_rcv; } ;
struct xinpcb {int /*<<< orphan*/  inp_vflag; int /*<<< orphan*/  inp_inc; } ;
struct netinfo {int /*<<< orphan*/  ni_sndcc; int /*<<< orphan*/  ni_rcvcc; } ;

/* Variables and functions */
 struct netinfo* enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void
enter_sysctl(struct xinpcb *xip, struct xsocket *so, int state,
    const char *proto)
{
	struct netinfo *p;

	if ((p = enter(&xip->inp_inc, xip->inp_vflag, state, proto)) != NULL) {
		p->ni_rcvcc = so->so_rcv.sb_cc;
		p->ni_sndcc = so->so_snd.sb_cc;
	}
}