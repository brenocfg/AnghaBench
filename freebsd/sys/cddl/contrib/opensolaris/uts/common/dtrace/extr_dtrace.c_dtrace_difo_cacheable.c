#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_4__ {scalar_t__ dtdv_scope; int dtdv_id; } ;
typedef  TYPE_1__ dtrace_difv_t ;
struct TYPE_5__ {int dtdo_varlen; int dtdo_len; int /*<<< orphan*/ * dtdo_buf; TYPE_1__* dtdo_vartab; } ;
typedef  TYPE_2__ dtrace_difo_t ;

/* Variables and functions */
 scalar_t__ DIFV_SCOPE_GLOBAL ; 
 scalar_t__ DIF_INSTR_OP (int /*<<< orphan*/ ) ; 
 scalar_t__ DIF_OP_LDGA ; 
 scalar_t__ DIF_OP_LDSB ; 
 scalar_t__ DIF_OP_LDX ; 
 scalar_t__ DIF_OP_RLDSB ; 
 scalar_t__ DIF_OP_RLDX ; 
 scalar_t__ DIF_OP_STTS ; 
 scalar_t__ DIF_OP_ULDSB ; 
 scalar_t__ DIF_OP_ULDX ; 
#define  DIF_VAR_CURTHREAD 133 
#define  DIF_VAR_EXECARGS 132 
#define  DIF_VAR_EXECNAME 131 
#define  DIF_VAR_PID 130 
#define  DIF_VAR_TID 129 
#define  DIF_VAR_ZONENAME 128 

__attribute__((used)) static int
dtrace_difo_cacheable(dtrace_difo_t *dp)
{
	int i;

	if (dp == NULL)
		return (0);

	for (i = 0; i < dp->dtdo_varlen; i++) {
		dtrace_difv_t *v = &dp->dtdo_vartab[i];

		if (v->dtdv_scope != DIFV_SCOPE_GLOBAL)
			continue;

		switch (v->dtdv_id) {
		case DIF_VAR_CURTHREAD:
		case DIF_VAR_PID:
		case DIF_VAR_TID:
		case DIF_VAR_EXECARGS:
		case DIF_VAR_EXECNAME:
		case DIF_VAR_ZONENAME:
			break;

		default:
			return (0);
		}
	}

	/*
	 * This DIF object may be cacheable.  Now we need to look for any
	 * array loading instructions, any memory loading instructions, or
	 * any stores to thread-local variables.
	 */
	for (i = 0; i < dp->dtdo_len; i++) {
		uint_t op = DIF_INSTR_OP(dp->dtdo_buf[i]);

		if ((op >= DIF_OP_LDSB && op <= DIF_OP_LDX) ||
		    (op >= DIF_OP_ULDSB && op <= DIF_OP_ULDX) ||
		    (op >= DIF_OP_RLDSB && op <= DIF_OP_RLDX) ||
		    op == DIF_OP_LDGA || op == DIF_OP_STTS)
			return (0);
	}

	return (1);
}