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
struct ecore_bmap {scalar_t__ max_count; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 scalar_t__ OSAL_FIND_FIRST_BIT (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool ecore_bmap_is_empty(struct ecore_bmap *bmap)
{
	return (bmap->max_count ==
		OSAL_FIND_FIRST_BIT(bmap->bitmap, bmap->max_count));
}