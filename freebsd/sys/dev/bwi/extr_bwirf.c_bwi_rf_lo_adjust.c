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
struct bwi_tpctl {int dummy; } ;
struct bwi_rf_lo {int dummy; } ;
struct bwi_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_LO_WRITE (struct bwi_mac*,struct bwi_rf_lo const*) ; 
 struct bwi_rf_lo* bwi_rf_lo_find (struct bwi_mac*,struct bwi_tpctl const*) ; 

void
bwi_rf_lo_adjust(struct bwi_mac *mac, const struct bwi_tpctl *tpctl)
{
	const struct bwi_rf_lo *lo;

	lo = bwi_rf_lo_find(mac, tpctl);
	RF_LO_WRITE(mac, lo);
}