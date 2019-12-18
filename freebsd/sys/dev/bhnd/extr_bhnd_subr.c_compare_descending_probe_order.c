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
 int compare_ascending_probe_order (void const*,void const*) ; 

__attribute__((used)) static int
compare_descending_probe_order(const void *lhs, const void *rhs)
{
	return (compare_ascending_probe_order(rhs, lhs));
}