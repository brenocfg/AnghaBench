#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vec; } ;
struct TYPE_4__ {TYPE_1__ aprox_match; } ;
struct ecore_mcast_obj {TYPE_2__ registry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_VEC64_CLEAR_BIT (int /*<<< orphan*/ ,int) ; 
 int ecore_mcast_get_next_bin (struct ecore_mcast_obj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_mcast_clear_first_bin(struct ecore_mcast_obj *o)
{
	int cur_bit = ecore_mcast_get_next_bin(o, 0);

	if (cur_bit >= 0)
		BIT_VEC64_CLEAR_BIT(o->registry.aprox_match.vec, cur_bit);

	return cur_bit;
}