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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct inpcb {int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; TYPE_2__ inp_faddr; TYPE_1__ inp_laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_LOCK_ASSERT (struct inpcb*) ; 

void
inp_4tuple_get(struct inpcb *inp, uint32_t *laddr, uint16_t *lp,
    uint32_t *faddr, uint16_t *fp)
{

	INP_LOCK_ASSERT(inp);
	*laddr = inp->inp_laddr.s_addr;
	*faddr = inp->inp_faddr.s_addr;
	*lp = inp->inp_lport;
	*fp = inp->inp_fport;
}