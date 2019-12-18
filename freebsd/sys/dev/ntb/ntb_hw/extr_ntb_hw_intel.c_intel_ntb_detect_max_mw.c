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
struct ntb_softc {scalar_t__ type; int /*<<< orphan*/  mw_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_MW_COUNT ; 
 scalar_t__ HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ NTB_ATOM ; 
 int /*<<< orphan*/  NTB_SPLIT_BAR ; 
 int /*<<< orphan*/  XEON_HSX_SPLIT_MW_COUNT ; 
 int /*<<< orphan*/  XEON_SNB_MW_COUNT ; 

__attribute__((used)) static void
intel_ntb_detect_max_mw(struct ntb_softc *ntb)
{

	if (ntb->type == NTB_ATOM) {
		ntb->mw_count = ATOM_MW_COUNT;
		return;
	}

	if (HAS_FEATURE(ntb, NTB_SPLIT_BAR))
		ntb->mw_count = XEON_HSX_SPLIT_MW_COUNT;
	else
		ntb->mw_count = XEON_SNB_MW_COUNT;
}