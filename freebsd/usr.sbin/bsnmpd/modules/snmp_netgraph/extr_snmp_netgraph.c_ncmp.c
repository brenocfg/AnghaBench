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
struct nodeinfo {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static int
ncmp(const void *p1, const void *p2)
{
	const struct nodeinfo *i1 = p1;
	const struct nodeinfo *i2 = p2;

	if (i1->id < i2->id)
		return (-1);
	if (i1->id > i2->id)
		return (+1);
	return (0);
}