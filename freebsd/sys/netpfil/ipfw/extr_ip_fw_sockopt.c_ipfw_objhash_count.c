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
typedef  int /*<<< orphan*/  uint32_t ;
struct namedobj_instance {int /*<<< orphan*/  count; } ;

/* Variables and functions */

uint32_t
ipfw_objhash_count(struct namedobj_instance *ni)
{

	return (ni->count);
}