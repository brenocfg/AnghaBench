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
struct pps_state {int kcmode; int driver_abi; } ;

/* Variables and functions */
 int KCMODE_ABIFLAG ; 

__attribute__((used)) static inline int
abi_aware(struct pps_state *pps, int vers)
{

	return ((pps->kcmode & KCMODE_ABIFLAG) && pps->driver_abi >= vers);
}