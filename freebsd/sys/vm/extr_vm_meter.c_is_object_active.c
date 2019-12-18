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
typedef  TYPE_1__* vm_object_t ;
struct TYPE_3__ {scalar_t__ ref_count; scalar_t__ shadow_count; } ;

/* Variables and functions */

__attribute__((used)) static bool
is_object_active(vm_object_t obj)
{

	return (obj->ref_count > obj->shadow_count);
}