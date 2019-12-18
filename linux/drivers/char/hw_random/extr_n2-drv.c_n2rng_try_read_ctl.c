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
struct n2rng {int hvapi_major; } ;

/* Variables and functions */
#define  HV_ENOACCESS 129 
 unsigned long HV_EOK ; 
#define  HV_EWOULDBLOCK 128 
 int n2rng_hv_err_trans (unsigned long) ; 
 unsigned long sun4v_rng_ctl_read_v2 (unsigned long,unsigned long,unsigned long*,unsigned long*,unsigned long*,unsigned long*) ; 
 unsigned long sun4v_rng_get_diag_ctl () ; 

__attribute__((used)) static int n2rng_try_read_ctl(struct n2rng *np)
{
	unsigned long hv_err;
	unsigned long x;

	if (np->hvapi_major == 1) {
		hv_err = sun4v_rng_get_diag_ctl();
	} else {
		/* We purposefully give invalid arguments, HV_NOACCESS
		 * is higher priority than the errors we'd get from
		 * these other cases, and that's the error we are
		 * truly interested in.
		 */
		hv_err = sun4v_rng_ctl_read_v2(0UL, ~0UL, &x, &x, &x, &x);
		switch (hv_err) {
		case HV_EWOULDBLOCK:
		case HV_ENOACCESS:
			break;
		default:
			hv_err = HV_EOK;
			break;
		}
	}

	return n2rng_hv_err_trans(hv_err);
}