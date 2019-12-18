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
struct unpcb {int dummy; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  socantsendmore (struct socket*) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_shutdown (struct unpcb*) ; 

__attribute__((used)) static int
uipc_shutdown(struct socket *so)
{
	struct unpcb *unp;

	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("uipc_shutdown: unp == NULL"));

	UNP_PCB_LOCK(unp);
	socantsendmore(so);
	unp_shutdown(unp);
	UNP_PCB_UNLOCK(unp);
	return (0);
}