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
struct refspec_item {scalar_t__ exact_sha1; scalar_t__ matching; scalar_t__ pattern; scalar_t__ force; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 

void refspec_item_clear(struct refspec_item *item)
{
	FREE_AND_NULL(item->src);
	FREE_AND_NULL(item->dst);
	item->force = 0;
	item->pattern = 0;
	item->matching = 0;
	item->exact_sha1 = 0;
}