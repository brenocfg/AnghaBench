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
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static inline int64_t div64_s64_precise(int64_t a, int64_t b)
{
	int64_t r, al;

	al = a << 16;
	r = (al * 2 + 1) / (2 * b);
	return r >> 16;
}