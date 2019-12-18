#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uleb128_t ;
struct unwind_state {TYPE_1__* regs; } ;
typedef  enum item_location { ____Placeholder_item_location } item_location ;
struct TYPE_2__ {int where; size_t value; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
#define  Memory 131 
#define  Nowhere 130 
#define  Register 129 
#define  Value 128 
 int /*<<< orphan*/  unw_debug (char*,...) ; 

__attribute__((used)) static void set_rule(uleb128_t reg, enum item_location where, uleb128_t value,
		     struct unwind_state *state)
{
	if (reg < ARRAY_SIZE(state->regs)) {
		state->regs[reg].where = where;
		state->regs[reg].value = value;

#ifdef UNWIND_DEBUG
		unw_debug("r%lu: ", reg);
		switch (where) {
		case Nowhere:
			unw_debug("s ");
			break;
		case Memory:
			unw_debug("c(%lu) ", value);
			break;
		case Register:
			unw_debug("r(%lu) ", value);
			break;
		case Value:
			unw_debug("v(%lu) ", value);
			break;
		default:
			break;
		}
#endif
	}
}