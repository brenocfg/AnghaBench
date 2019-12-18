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
typedef  int /*<<< orphan*/  efx_phy_cap_type_t ;
typedef  int efx_link_mode_t ;

/* Variables and functions */
#define  EFX_LINK_100000FDX 138 
#define  EFX_LINK_10000FDX 137 
#define  EFX_LINK_1000FDX 136 
#define  EFX_LINK_1000HDX 135 
#define  EFX_LINK_100FDX 134 
#define  EFX_LINK_100HDX 133 
#define  EFX_LINK_10FDX 132 
#define  EFX_LINK_10HDX 131 
#define  EFX_LINK_25000FDX 130 
#define  EFX_LINK_40000FDX 129 
#define  EFX_LINK_50000FDX 128 
 int /*<<< orphan*/  EFX_PHY_CAP_100000FDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_10000FDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_1000FDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_1000HDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_100FDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_100HDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_10FDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_10HDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_25000FDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_40000FDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_50000FDX ; 
 int /*<<< orphan*/  EFX_PHY_CAP_INVALID ; 

__attribute__((used)) static efx_phy_cap_type_t
sfxge_link_mode_to_phy_cap(efx_link_mode_t mode)
{
	switch (mode) {
	case EFX_LINK_10HDX:
		return (EFX_PHY_CAP_10HDX);
	case EFX_LINK_10FDX:
		return (EFX_PHY_CAP_10FDX);
	case EFX_LINK_100HDX:
		return (EFX_PHY_CAP_100HDX);
	case EFX_LINK_100FDX:
		return (EFX_PHY_CAP_100FDX);
	case EFX_LINK_1000HDX:
		return (EFX_PHY_CAP_1000HDX);
	case EFX_LINK_1000FDX:
		return (EFX_PHY_CAP_1000FDX);
	case EFX_LINK_10000FDX:
		return (EFX_PHY_CAP_10000FDX);
	case EFX_LINK_25000FDX:
		return (EFX_PHY_CAP_25000FDX);
	case EFX_LINK_40000FDX:
		return (EFX_PHY_CAP_40000FDX);
	case EFX_LINK_50000FDX:
		return (EFX_PHY_CAP_50000FDX);
	case EFX_LINK_100000FDX:
		return (EFX_PHY_CAP_100000FDX);
	default:
		return (EFX_PHY_CAP_INVALID);
	}
}