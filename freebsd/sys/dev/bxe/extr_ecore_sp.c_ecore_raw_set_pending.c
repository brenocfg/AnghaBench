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
 int /*<<< orphan*/  ECORE_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_SMP_MB_AFTER_CLEAR_BIT () ; 
 int /*<<< orphan*/  ECORE_SMP_MB_BEFORE_CLEAR_BIT () ; 

__attribute__((used)) static void ecore_raw_set_pending(struct ecore_raw_obj *o)
{
	ECORE_SMP_MB_BEFORE_CLEAR_BIT();
	ECORE_SET_BIT(o->state, o->pstate);
	ECORE_SMP_MB_AFTER_CLEAR_BIT();
}