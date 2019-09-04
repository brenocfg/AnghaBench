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
struct string_list_item {int /*<<< orphan*/  util; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_by_st_size(const void *a, const void *b)
{
	intptr_t x = (intptr_t)((struct string_list_item *)a)->util;
	intptr_t y = (intptr_t)((struct string_list_item *)b)->util;

	return x > y ? -1 : (x < y ? +1 : 0);
}