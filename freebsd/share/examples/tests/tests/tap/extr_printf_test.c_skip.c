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
 int /*<<< orphan*/  printf (char*,int) ; 
 int test_num ; 

__attribute__((used)) static void
skip(int skip_num)
{
	int i;

	for (i = 0; i < skip_num; i++) {
		printf("not ok %d # SKIP\n", test_num);
		test_num++;
	}
}