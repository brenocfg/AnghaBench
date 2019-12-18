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
typedef  scalar_t__ dss_prec_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACQUIRE ; 
 scalar_t__ atomic_load_u (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_prec_default ; 
 scalar_t__ dss_prec_disabled ; 
 int /*<<< orphan*/  have_dss ; 

dss_prec_t
extent_dss_prec_get(void) {
	dss_prec_t ret;

	if (!have_dss) {
		return dss_prec_disabled;
	}
	ret = (dss_prec_t)atomic_load_u(&dss_prec_default, ATOMIC_ACQUIRE);
	return ret;
}