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
typedef  int /*<<< orphan*/  u8 ;
struct nlattr {int dummy; } ;
struct hostapd_hw_modes {int /*<<< orphan*/  vht_mcs_set; int /*<<< orphan*/  vht_capab; } ;

/* Variables and functions */
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void phy_info_vht_capa(struct hostapd_hw_modes *mode,
			      struct nlattr *capa,
			      struct nlattr *mcs_set)
{
	if (capa)
		mode->vht_capab = nla_get_u32(capa);

	if (mcs_set && nla_len(mcs_set) >= 8) {
		u8 *mcs;
		mcs = nla_data(mcs_set);
		os_memcpy(mode->vht_mcs_set, mcs, 8);
	}
}