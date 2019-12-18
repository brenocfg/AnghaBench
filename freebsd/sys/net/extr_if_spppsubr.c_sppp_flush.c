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
struct sppp {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 struct sppp* IFP2SP (struct ifnet*) ; 
 int /*<<< orphan*/  SPPP_LOCK (struct sppp*) ; 
 int /*<<< orphan*/  SPPP_UNLOCK (struct sppp*) ; 
 int /*<<< orphan*/  sppp_flush_unlocked (struct ifnet*) ; 

void
sppp_flush(struct ifnet *ifp)
{
	struct sppp *sp = IFP2SP(ifp);

	SPPP_LOCK(sp);
	sppp_flush_unlocked (ifp);
	SPPP_UNLOCK(sp);
}