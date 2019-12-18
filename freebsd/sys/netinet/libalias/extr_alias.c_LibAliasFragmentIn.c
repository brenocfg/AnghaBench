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
struct libalias {int dummy; } ;
struct ip {int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_sum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DifferentialChecksum (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 

void
LibAliasFragmentIn(struct libalias *la, char *ptr,	/* Points to correctly
							 * de-aliased header
							 * fragment */
    char *ptr_fragment		/* Points to fragment which must be
				 * de-aliased   */
)
{
	struct ip *pip;
	struct ip *fpip;

	LIBALIAS_LOCK(la);
	(void)la;
	pip = (struct ip *)ptr;
	fpip = (struct ip *)ptr_fragment;

	DifferentialChecksum(&fpip->ip_sum,
	    &pip->ip_dst, &fpip->ip_dst, 2);
	fpip->ip_dst = pip->ip_dst;
	LIBALIAS_UNLOCK(la);
}