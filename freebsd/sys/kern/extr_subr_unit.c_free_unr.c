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
typedef  int /*<<< orphan*/  u_int ;
struct unrhdr {int /*<<< orphan*/  mtx; } ;
struct unr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Free (void*) ; 
 void* Malloc (int) ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clean_unrhdrl (struct unrhdr*) ; 
 int /*<<< orphan*/  free_unrl (struct unrhdr*,int /*<<< orphan*/ ,void**,void**) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 

void
free_unr(struct unrhdr *uh, u_int item)
{
	void *p1, *p2;

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL, "free_unr");
	p1 = Malloc(sizeof(struct unr));
	p2 = Malloc(sizeof(struct unr));
	mtx_lock(uh->mtx);
	free_unrl(uh, item, &p1, &p2);
	clean_unrhdrl(uh);
	mtx_unlock(uh->mtx);
	if (p1 != NULL)
		Free(p1);
	if (p2 != NULL)
		Free(p2);
}