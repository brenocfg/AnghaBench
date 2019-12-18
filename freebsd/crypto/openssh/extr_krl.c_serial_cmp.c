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
struct revoked_serial {scalar_t__ hi; scalar_t__ lo; } ;

/* Variables and functions */

__attribute__((used)) static int
serial_cmp(struct revoked_serial *a, struct revoked_serial *b)
{
	if (a->hi >= b->lo && a->lo <= b->hi)
		return 0;
	return a->lo < b->lo ? -1 : 1;
}