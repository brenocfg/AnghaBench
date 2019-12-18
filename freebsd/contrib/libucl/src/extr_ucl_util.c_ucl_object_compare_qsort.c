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
typedef  int /*<<< orphan*/  ucl_object_t ;

/* Variables and functions */
 int ucl_object_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int
ucl_object_compare_qsort (const ucl_object_t **o1,
		const ucl_object_t **o2)
{
	return ucl_object_compare (*o1, *o2);
}