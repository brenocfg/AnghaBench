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
struct nd_defrouter {int dummy; } ;
struct nd6_drhead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND6_WLOCK () ; 
 int /*<<< orphan*/  ND6_WUNLOCK () ; 
 struct nd_defrouter* TAILQ_FIRST (struct nd6_drhead*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct nd6_drhead*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct nd6_drhead*,struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 struct nd6_drhead V_nd6_defrouter ; 
 int /*<<< orphan*/  defrouter_del (struct nd_defrouter*) ; 
 int /*<<< orphan*/  defrouter_unlink (struct nd_defrouter*,struct nd6_drhead*) ; 
 int /*<<< orphan*/  dr_entry ; 

void
nd6_defrouter_flush_all(void)
{
	struct nd_defrouter *dr;
	struct nd6_drhead drq;

	TAILQ_INIT(&drq);

	ND6_WLOCK();
	while ((dr = TAILQ_FIRST(&V_nd6_defrouter)) != NULL)
		defrouter_unlink(dr, &drq);
	ND6_WUNLOCK();

	while ((dr = TAILQ_FIRST(&drq)) != NULL) {
		TAILQ_REMOVE(&drq, dr, dr_entry);
		defrouter_del(dr);
	}
}