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
struct socket {int so_state; int /*<<< orphan*/  so_timeo; int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  SOLISTENING (struct socket*) ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int SS_ISDISCONNECTED ; 
 int SS_ISDISCONNECTING ; 
 int /*<<< orphan*/  sbdrop_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socantrcvmore_locked (struct socket*) ; 
 int /*<<< orphan*/  socantsendmore_locked (struct socket*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
soisdisconnected(struct socket *so)
{

	SOCK_LOCK(so);
	so->so_state &= ~(SS_ISCONNECTING|SS_ISCONNECTED|SS_ISDISCONNECTING);
	so->so_state |= SS_ISDISCONNECTED;

	if (!SOLISTENING(so)) {
		SOCK_UNLOCK(so);
		SOCKBUF_LOCK(&so->so_rcv);
		socantrcvmore_locked(so);
		SOCKBUF_LOCK(&so->so_snd);
		sbdrop_locked(&so->so_snd, sbused(&so->so_snd));
		socantsendmore_locked(so);
	} else
		SOCK_UNLOCK(so);
	wakeup(&so->so_timeo);
}