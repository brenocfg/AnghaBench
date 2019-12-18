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
struct ifnet {int dummy; } ;
struct epair_dpcpu {int dummy; } ;

/* Variables and functions */
 struct epair_dpcpu* DPCPU_ID_PTR (int /*<<< orphan*/ ,struct epair_dpcpu*) ; 
 int /*<<< orphan*/  EPAIR_LOCK (struct epair_dpcpu*) ; 
 int /*<<< orphan*/  EPAIR_UNLOCK (struct epair_dpcpu*) ; 
 int /*<<< orphan*/  cpuid_from_ifp (struct ifnet*) ; 
 int /*<<< orphan*/  epair_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
epair_start(struct ifnet *ifp)
{
	struct epair_dpcpu *epair_dpcpu;

	epair_dpcpu = DPCPU_ID_PTR(cpuid_from_ifp(ifp), epair_dpcpu);
	EPAIR_LOCK(epair_dpcpu);
	epair_start_locked(ifp);
	EPAIR_UNLOCK(epair_dpcpu);
}