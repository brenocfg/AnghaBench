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

void test_index_tests__sort0(void)
{
	/* sort the entires in an index */

   /*
   * TODO: This no longer applies:
   * index sorting in Git uses some specific changes to the way
   * directories are sorted.
   *
   * We need to specificially check for this by creating a new
   * index, adding entries in random order and then
   * checking for consistency
   */
}