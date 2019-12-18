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
struct bitmap {size_t top; size_t len; scalar_t__* d; } ;

/* Variables and functions */

__attribute__((used)) static void
retop(struct bitmap *b)
{
	if (b->top >= b->len)
		return;
	while (b->top > 0 && b->d[b->top] == 0)
		b->top--;
}