#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ ldns_radix_t ;

/* Variables and functions */

void
ldns_radix_init(ldns_radix_t* tree)
{
	/** Initialize it */
	if (tree) {
		tree->root = NULL;
		tree->count = 0;
	}
	return;
}