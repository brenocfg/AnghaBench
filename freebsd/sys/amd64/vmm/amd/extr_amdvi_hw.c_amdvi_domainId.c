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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int AMDVI_MAX_DOMAIN ; 
 int amdvi_dom_id ; 

__attribute__((used)) static uint16_t
amdvi_domainId(void)
{

	/*
	 * If we hit maximum domain limit, rollover leaving host
	 * domain(0).
	 * XXX: make sure that this domain is not used.
	 */
	if (amdvi_dom_id == AMDVI_MAX_DOMAIN)
		amdvi_dom_id = 1;

	return ((uint16_t)amdvi_dom_id++);
}