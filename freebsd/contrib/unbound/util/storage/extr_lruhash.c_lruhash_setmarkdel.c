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
struct lruhash {int /*<<< orphan*/  lock; int /*<<< orphan*/  markdelfunc; } ;
typedef  int /*<<< orphan*/  lruhash_markdelfunc_type ;

/* Variables and functions */
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 

void 
lruhash_setmarkdel(struct lruhash* table, lruhash_markdelfunc_type md)
{
	lock_quick_lock(&table->lock);
	table->markdelfunc = md;
	lock_quick_unlock(&table->lock);
}