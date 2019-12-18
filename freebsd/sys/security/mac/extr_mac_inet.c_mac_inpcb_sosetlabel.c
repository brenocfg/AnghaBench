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
struct socket {int /*<<< orphan*/  so_label; } ;
struct inpcb {int /*<<< orphan*/  inp_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ,struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_LOCK_ASSERT (struct socket*) ; 
 int /*<<< orphan*/  inpcb_sosetlabel ; 

void
mac_inpcb_sosetlabel(struct socket *so, struct inpcb *inp)
{

	INP_WLOCK_ASSERT(inp);
	SOCK_LOCK_ASSERT(so);

	MAC_POLICY_PERFORM_NOSLEEP(inpcb_sosetlabel, so, so->so_label, inp,
	    inp->inp_label);
}