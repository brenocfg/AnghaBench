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
 int /*<<< orphan*/  COMPARE_ARRAYS (int*,int*,int) ; 

__attribute__((used)) static int
compare_secflavor(int *sec1, int *sec2, int nsec)
{

	COMPARE_ARRAYS(sec1, sec2, nsec);
}