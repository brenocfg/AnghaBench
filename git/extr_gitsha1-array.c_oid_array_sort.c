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
struct oid_array {int sorted; int /*<<< orphan*/  nr; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_hashcmp ; 

__attribute__((used)) static void oid_array_sort(struct oid_array *array)
{
	QSORT(array->oid, array->nr, void_hashcmp);
	array->sorted = 1;
}