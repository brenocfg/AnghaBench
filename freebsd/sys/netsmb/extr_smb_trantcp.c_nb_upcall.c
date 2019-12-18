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
struct socket {int dummy; } ;
struct nbpcb {int /*<<< orphan*/ * nbp_selectid; } ;

/* Variables and functions */
 int SU_OK ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nb_upcall(struct socket *so, void *arg, int waitflag)
{
	struct nbpcb *nbp = arg;

	if (arg == NULL || nbp->nbp_selectid == NULL)
		return (SU_OK);
	wakeup(nbp->nbp_selectid);
	return (SU_OK);
}