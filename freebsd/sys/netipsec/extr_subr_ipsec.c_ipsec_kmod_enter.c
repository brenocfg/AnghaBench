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
typedef  int u_int ;

/* Variables and functions */
 int ENXIO ; 
 int IPSEC_MODULE_ENABLED ; 
 int IPSEC_MODULE_INCR ; 
 scalar_t__ atomic_cmpset_acq_int (int volatile*,int,int) ; 

__attribute__((used)) static int
ipsec_kmod_enter(volatile u_int *cntr)
{
	u_int old, new;

	do {
		old = *cntr;
		if ((old & IPSEC_MODULE_ENABLED) == 0)
			return (ENXIO);
		new = old + IPSEC_MODULE_INCR;
	} while(atomic_cmpset_acq_int(cntr, old, new) == 0);
	return (0);
}