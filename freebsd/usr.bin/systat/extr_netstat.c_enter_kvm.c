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
struct TYPE_4__ {int /*<<< orphan*/  sb_ccc; } ;
struct TYPE_3__ {int /*<<< orphan*/  sb_ccc; } ;
struct socket {TYPE_2__ so_snd; TYPE_1__ so_rcv; } ;
struct netinfo {int /*<<< orphan*/  ni_sndcc; int /*<<< orphan*/  ni_rcvcc; } ;
struct inpcb {int /*<<< orphan*/  inp_vflag; int /*<<< orphan*/  inp_inc; } ;

/* Variables and functions */
 struct netinfo* enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void
enter_kvm(struct inpcb *inp, struct socket *so, int state, const char *proto)
{
	struct netinfo *p;

	if ((p = enter(&inp->inp_inc, inp->inp_vflag, state, proto)) != NULL) {
		p->ni_rcvcc = so->so_rcv.sb_ccc;
		p->ni_sndcc = so->so_snd.sb_ccc;
	}
}