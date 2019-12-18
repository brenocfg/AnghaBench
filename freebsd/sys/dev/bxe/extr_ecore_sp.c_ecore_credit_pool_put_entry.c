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
struct ecore_credit_pool_obj {int base_pool_offset; int pool_sz; int /*<<< orphan*/  pool_mirror; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_VEC64_SET_BIT (int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static bool ecore_credit_pool_put_entry(
	struct ecore_credit_pool_obj *o,
	int offset)
{
	if (offset < o->base_pool_offset)
		return FALSE;

	offset -= o->base_pool_offset;

	if (offset >= o->pool_sz)
		return FALSE;

	/* Return the entry to the pool */
	BIT_VEC64_SET_BIT(o->pool_mirror, offset);

	return TRUE;
}