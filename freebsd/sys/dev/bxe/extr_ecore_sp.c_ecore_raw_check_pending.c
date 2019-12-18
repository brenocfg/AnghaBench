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
struct ecore_raw_obj {int /*<<< orphan*/  pstate; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ecore_raw_check_pending(struct ecore_raw_obj *o)
{
	/*
     * !! converts the value returned by ECORE_TEST_BIT such that it
     * is guaranteed not to be truncated regardless of bool definition.
	 *
	 * Note we cannot simply define the function's return value type
     * to match the type returned by ECORE_TEST_BIT, as it varies by
     * platform/implementation.
	 */

	return !!ECORE_TEST_BIT(o->state, o->pstate);
}