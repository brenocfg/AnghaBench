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
struct val_neg_cache {int use; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

size_t val_neg_get_mem(struct val_neg_cache* neg)
{
	size_t result;
	lock_basic_lock(&neg->lock);
	result = sizeof(*neg) + neg->use;
	lock_basic_unlock(&neg->lock);
	return result;
}