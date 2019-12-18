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
struct witness {size_t w_index; } ;

/* Variables and functions */
 int WITNESS_LOCK_ORDER_KNOWN ; 
 scalar_t__ isitmychild (struct witness*,struct witness*) ; 
 int** w_rmatrix ; 

__attribute__((used)) static int
witness_lock_order_check(struct witness *parent, struct witness *child)
{

	if (parent != child &&
	    w_rmatrix[parent->w_index][child->w_index]
	    & WITNESS_LOCK_ORDER_KNOWN &&
	    isitmychild(parent, child))
		return (1);

	return (0);
}