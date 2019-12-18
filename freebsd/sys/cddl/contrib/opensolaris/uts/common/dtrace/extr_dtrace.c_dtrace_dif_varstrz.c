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
typedef  int /*<<< orphan*/  dtrace_state_t ;
struct TYPE_3__ {size_t dtms_scratch_ptr; size_t dtms_scratch_base; size_t dtms_scratch_size; } ;
typedef  TYPE_1__ dtrace_mstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_NOSCRATCH ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_bcopy (void const*,void*,size_t) ; 

__attribute__((used)) static uintptr_t
dtrace_dif_varstrz(uintptr_t addr, size_t strsz, dtrace_state_t *state,
    dtrace_mstate_t *mstate)
{
	char *p;
	size_t i;
	uintptr_t ret;

	if (mstate->dtms_scratch_ptr + strsz >
	    mstate->dtms_scratch_base + mstate->dtms_scratch_size) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
		return (0);
	}

	dtrace_bcopy((const void *)addr, (void *)mstate->dtms_scratch_ptr,
	    strsz);

	/* Replace sub-string termination characters with a space. */
	for (p = (char *) mstate->dtms_scratch_ptr, i = 0; i < strsz - 1;
	    p++, i++)
		if (*p == '\0')
			*p = ' ';

	ret = mstate->dtms_scratch_ptr;
	mstate->dtms_scratch_ptr += strsz;
	return (ret);
}