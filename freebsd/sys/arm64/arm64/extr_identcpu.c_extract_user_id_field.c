#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ CPU_DESC_FIELD (int /*<<< orphan*/ ,int) ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  user_cpu_desc ; 
 TYPE_1__* user_regs ; 

bool
extract_user_id_field(u_int reg, u_int field_shift, uint8_t *val)
{
	uint64_t value;
	int i;

	for (i = 0; i < nitems(user_regs); i++) {
		if (user_regs[i].reg == reg) {
			value = CPU_DESC_FIELD(user_cpu_desc, i);
			*val = value >> field_shift;
			return (true);
		}
	}

	return (false);
}