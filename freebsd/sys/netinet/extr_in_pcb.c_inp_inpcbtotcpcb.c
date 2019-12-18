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
struct tcpcb {int dummy; } ;
struct inpcb {scalar_t__ inp_ppcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 

struct tcpcb *
inp_inpcbtotcpcb(struct inpcb *inp)
{

	INP_WLOCK_ASSERT(inp);
	return ((struct tcpcb *)inp->inp_ppcb);
}