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
 int pack_copy_priority (char const*) ; 

__attribute__((used)) static int pack_copy_cmp(const char *a, const char *b)
{
	return pack_copy_priority(a) - pack_copy_priority(b);
}