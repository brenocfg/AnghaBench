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
struct domain {int /*<<< orphan*/  pt_levels; int /*<<< orphan*/  ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VTD ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  domain ; 
 int /*<<< orphan*/  domhead ; 
 int /*<<< orphan*/  free (struct domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  vtd_free_ptp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtd_destroy_domain(void *arg)
{
	struct domain *dom;
	
	dom = arg;

	SLIST_REMOVE(&domhead, dom, domain, next);
	vtd_free_ptp(dom->ptp, dom->pt_levels);
	free(dom, M_VTD);
}