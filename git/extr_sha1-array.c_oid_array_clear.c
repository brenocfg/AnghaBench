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
struct oid_array {scalar_t__ sorted; scalar_t__ alloc; scalar_t__ nr; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 

void oid_array_clear(struct oid_array *array)
{
	FREE_AND_NULL(array->oid);
	array->nr = 0;
	array->alloc = 0;
	array->sorted = 0;
}