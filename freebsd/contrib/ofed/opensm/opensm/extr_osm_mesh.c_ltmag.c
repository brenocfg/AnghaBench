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

__attribute__((used)) static inline int ltmag(int a, int b)
{
	int a1 = (a >= 0)? a : -a;
	int b1 = (b >= 0)? b : -b;

	return (a1 < b1) || (a1 == b1 && a > b);
}