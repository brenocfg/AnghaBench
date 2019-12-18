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
struct cb_id {scalar_t__ idx; scalar_t__ val; } ;

/* Variables and functions */

int cn_cb_equal(struct cb_id *i1, struct cb_id *i2)
{
	return ((i1->idx == i2->idx) && (i1->val == i2->val));
}