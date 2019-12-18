#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* dcr_cred; } ;
struct TYPE_7__ {TYPE_1__ dts_cred; } ;
typedef  TYPE_2__ dtrace_state_t ;
struct TYPE_8__ {scalar_t__ cr_zone; } ;
typedef  TYPE_3__ cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_3__* CRED () ; 

__attribute__((used)) static int
dtrace_priv_proc_common_zone(dtrace_state_t *state)
{
#ifdef illumos
	cred_t *cr, *s_cr = state->dts_cred.dcr_cred;

	/*
	 * We should always have a non-NULL state cred here, since if cred
	 * is null (anonymous tracing), we fast-path bypass this routine.
	 */
	ASSERT(s_cr != NULL);

	if ((cr = CRED()) != NULL && s_cr->cr_zone == cr->cr_zone)
		return (1);

	return (0);
#else
	return (1);
#endif
}