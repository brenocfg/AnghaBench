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
struct refspec_item {int dummy; } ;
struct refspec {scalar_t__ raw_nr; struct refspec_item* raw; int /*<<< orphan*/  raw_alloc; scalar_t__ nr; struct refspec_item* items; int /*<<< orphan*/  alloc; int /*<<< orphan*/  fetch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct refspec_item*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refspec_item_init_or_die (struct refspec_item*,char const*,int /*<<< orphan*/ ) ; 
 struct refspec_item xstrdup (char const*) ; 

void refspec_append(struct refspec *rs, const char *refspec)
{
	struct refspec_item item;

	refspec_item_init_or_die(&item, refspec, rs->fetch);

	ALLOC_GROW(rs->items, rs->nr + 1, rs->alloc);
	rs->items[rs->nr++] = item;

	ALLOC_GROW(rs->raw, rs->raw_nr + 1, rs->raw_alloc);
	rs->raw[rs->raw_nr++] = xstrdup(refspec);
}