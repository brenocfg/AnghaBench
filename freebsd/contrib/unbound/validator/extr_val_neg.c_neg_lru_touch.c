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
struct val_neg_data {int dummy; } ;
struct val_neg_cache {struct val_neg_data* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  neg_lru_front (struct val_neg_cache*,struct val_neg_data*) ; 
 int /*<<< orphan*/  neg_lru_remove (struct val_neg_cache*,struct val_neg_data*) ; 

__attribute__((used)) static void neg_lru_touch(struct val_neg_cache* neg, 
	struct val_neg_data* data)
{
	if(data == neg->first)
		return; /* nothing to do */
	/* remove from current lru position */
	neg_lru_remove(neg, data);
	/* add at front */
	neg_lru_front(neg, data);
}