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
struct witness_lock_order_key {scalar_t__ from; scalar_t__ to; } ;

/* Variables and functions */

__attribute__((used)) static __inline int
witness_lock_order_key_equal(const struct witness_lock_order_key *a,
    const struct witness_lock_order_key *b)
{

	return (a->from == b->from && a->to == b->to);
}