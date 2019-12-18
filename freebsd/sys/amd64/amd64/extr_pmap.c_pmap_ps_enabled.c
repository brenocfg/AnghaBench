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
struct TYPE_3__ {int pm_flags; } ;

/* Variables and functions */
 int PMAP_PDE_SUPERPAGE ; 
 scalar_t__ pg_ps_enabled ; 

bool
pmap_ps_enabled(pmap_t pmap)
{

	return (pg_ps_enabled && (pmap->pm_flags & PMAP_PDE_SUPERPAGE) != 0);
}