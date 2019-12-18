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
struct bwi_rf_lo {int dummy; } ;
struct bwi_rf {int /*<<< orphan*/  rf_lo_used; struct bwi_rf_lo const* rf_lo; } ;
struct bwi_mac {struct bwi_rf mac_rf; } ;

/* Variables and functions */
 int BWI_RFLO_MAX ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int isset (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline int
bwi_rf_lo_isused(struct bwi_mac *mac, const struct bwi_rf_lo *lo)
{
	struct bwi_rf *rf = &mac->mac_rf;
	int idx;

	idx = lo - rf->rf_lo;
	KASSERT(idx >= 0 && idx < BWI_RFLO_MAX, ("idx %d", idx));

	return isset(rf->rf_lo_used, idx);
}