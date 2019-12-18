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
struct refspec {int nr; int raw_nr; scalar_t__ fetch; scalar_t__ raw_alloc; scalar_t__* raw; scalar_t__ alloc; scalar_t__* items; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (scalar_t__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  refspec_item_clear (scalar_t__*) ; 

void refspec_clear(struct refspec *rs)
{
	int i;

	for (i = 0; i < rs->nr; i++)
		refspec_item_clear(&rs->items[i]);

	FREE_AND_NULL(rs->items);
	rs->alloc = 0;
	rs->nr = 0;

	for (i = 0; i < rs->raw_nr; i++)
		free((char *)rs->raw[i]);
	FREE_AND_NULL(rs->raw);
	rs->raw_alloc = 0;
	rs->raw_nr = 0;

	rs->fetch = 0;
}