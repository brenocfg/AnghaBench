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
typedef  int ttb_entry_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {int /*<<< orphan*/  pm_pt1; } ;

/* Variables and functions */
 int ttb_flags ; 
 int vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline ttb_entry_t
pmap_ttb_get(pmap_t pmap)
{

	return (vtophys(pmap->pm_pt1) | ttb_flags);
}