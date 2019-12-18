#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ wc; } ;
typedef  TYPE_1__ charmap_t ;

/* Variables and functions */

__attribute__((used)) static int
cmap_compare_wc(const void *n1, const void *n2)
{
	const charmap_t *c1 = n1;
	const charmap_t *c2 = n2;

	return ((c1->wc < c2->wc) ? -1 : (c1->wc > c2->wc) ? 1 : 0);
}