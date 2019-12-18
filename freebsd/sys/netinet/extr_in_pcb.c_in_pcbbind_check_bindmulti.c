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
struct inpcb {int inp_flags2; TYPE_1__* inp_cred; } ;
struct TYPE_2__ {scalar_t__ cr_uid; } ;

/* Variables and functions */
 int INP_BINDMULTI ; 

int
in_pcbbind_check_bindmulti(const struct inpcb *ni, const struct inpcb *oi)
{
	/* Check permissions match */
	if ((ni->inp_flags2 & INP_BINDMULTI) &&
	    (ni->inp_cred->cr_uid !=
	    oi->inp_cred->cr_uid))
		return (0);

	/* Check the existing inp has BINDMULTI set */
	if ((ni->inp_flags2 & INP_BINDMULTI) &&
	    ((oi->inp_flags2 & INP_BINDMULTI) == 0))
		return (0);

	/*
	 * We're okay - either INP_BINDMULTI isn't set on ni, or
	 * it is and it matches the checks.
	 */
	return (1);
}