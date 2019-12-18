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
struct attr {size_t start; size_t end; } ;

/* Variables and functions */

__attribute__((used)) static int attrHasPos(struct attr *a, size_t pos)
{
	if (pos < a->start)
		return 0;
	return pos < a->end;
}