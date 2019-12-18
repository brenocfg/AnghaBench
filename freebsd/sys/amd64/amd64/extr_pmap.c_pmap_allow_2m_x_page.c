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
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {scalar_t__ pm_type; } ;

/* Variables and functions */
 scalar_t__ PT_EPT ; 
 int /*<<< orphan*/  pmap_allow_2m_x_ept ; 

__attribute__((used)) static bool
pmap_allow_2m_x_page(pmap_t pmap, bool executable)
{

	return (pmap->pm_type != PT_EPT || !executable ||
	    !pmap_allow_2m_x_ept);
}