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

/* Variables and functions */
 int /*<<< orphan*/  QSORT (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_ref_name ; 
 scalar_t__ ref_name ; 

__attribute__((used)) static void sort_ref_range(int bottom, int top)
{
	QSORT(ref_name + bottom, top - bottom, compare_ref_name);
}