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
typedef  int uint32_t ;
struct tegra_abpmisc_softc {int dummy; } ;
struct TYPE_2__ {int chip_id; int revision; } ;

/* Variables and functions */
 int ABP_RD4 (struct tegra_abpmisc_softc*,int) ; 
 int TEGRA_REVISION_A01 ; 
 int TEGRA_REVISION_A02 ; 
 int TEGRA_REVISION_A03 ; 
 int TEGRA_REVISION_A04 ; 
 int TEGRA_REVISION_UNKNOWN ; 
 TYPE_1__ tegra_sku_info ; 

__attribute__((used)) static void
tegra_abpmisc_read_revision(struct tegra_abpmisc_softc *sc)
{
	uint32_t id, chip_id, minor_rev;
	int rev;

	id = ABP_RD4(sc, 4);
	chip_id = (id >> 8) & 0xff;
	minor_rev = (id >> 16) & 0xf;

	switch (minor_rev) {
	case 1:
		rev = TEGRA_REVISION_A01;
		break;
	case 2:
		rev = TEGRA_REVISION_A02;
		break;
	case 3:
		rev = TEGRA_REVISION_A03;
		break;
	case 4:
		rev = TEGRA_REVISION_A04;
		break;
	default:
		rev = TEGRA_REVISION_UNKNOWN;
	}

	tegra_sku_info.chip_id = chip_id;
	tegra_sku_info.revision = rev;
}