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
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBJPR_CLEANONLY ; 
 unsigned long linux_invalidate_mapping_pages_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned long
linux_invalidate_mapping_pages(vm_object_t obj, pgoff_t start, pgoff_t end)
{

	return (linux_invalidate_mapping_pages_sub(obj, start, end, OBJPR_CLEANONLY));
}