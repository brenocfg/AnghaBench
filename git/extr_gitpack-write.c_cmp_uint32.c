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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_uint32(const void *a_, const void *b_)
{
	uint32_t a = *((uint32_t *)a_);
	uint32_t b = *((uint32_t *)b_);

	return (a < b) ? -1 : (a != b);
}