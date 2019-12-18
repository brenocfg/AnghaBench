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
struct ck_rhs_iterator {scalar_t__ offset; int /*<<< orphan*/ * cursor; } ;

/* Variables and functions */

void
ck_rhs_iterator_init(struct ck_rhs_iterator *iterator)
{

	iterator->cursor = NULL;
	iterator->offset = 0;
	return;
}