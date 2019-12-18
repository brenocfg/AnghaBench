#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {int pm_l0_paddr; int /*<<< orphan*/  pm_cookie; } ;

/* Variables and functions */
 int ASID_TO_OPERAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COOKIE_TO_ASID (int /*<<< orphan*/ ) ; 

uint64_t
pmap_to_ttbr0(pmap_t pmap)
{

	return (ASID_TO_OPERAND(COOKIE_TO_ASID(pmap->pm_cookie)) |
	    pmap->pm_l0_paddr);
}