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
struct val_neg_cache {scalar_t__ max; scalar_t__ use; scalar_t__ last; } ;

/* Variables and functions */
 int /*<<< orphan*/  neg_delete_data (struct val_neg_cache*,scalar_t__) ; 

__attribute__((used)) static void neg_make_space(struct val_neg_cache* neg, size_t need)
{
	/* delete elements until enough space or its empty */
	while(neg->last && neg->max < neg->use + need) {
		neg_delete_data(neg, neg->last);
	}
}