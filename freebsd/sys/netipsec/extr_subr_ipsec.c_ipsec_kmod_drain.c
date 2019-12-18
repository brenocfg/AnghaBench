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
 int IPSEC_MODULE_ENABLED ; 
 scalar_t__ atomic_cmpset_acq_int (int volatile*,int,int) ; 
 scalar_t__ atomic_cmpset_int (int volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void
ipsec_kmod_drain(volatile u_int *cntr)
{
	u_int old, new;

	do {
		old = *cntr;
		new = old & ~IPSEC_MODULE_ENABLED;
	} while (atomic_cmpset_acq_int(cntr, old, new) == 0);
	while (atomic_cmpset_int(cntr, 0, 0) == 0)
		pause("ipsecd", hz/2);
}