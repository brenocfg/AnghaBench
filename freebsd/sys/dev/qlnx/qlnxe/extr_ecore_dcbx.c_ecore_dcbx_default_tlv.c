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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ ECORE_ETH_TYPE_DEFAULT ; 
 int ecore_dcbx_app_ethtype (int /*<<< orphan*/ ) ; 
 int ecore_dcbx_ieee_app_ethtype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ecore_dcbx_default_tlv(u32 app_info_bitmap, u16 proto_id, bool ieee)
{
	bool ethtype;

	if (ieee)
		ethtype = ecore_dcbx_ieee_app_ethtype(app_info_bitmap);
	else
		ethtype = ecore_dcbx_app_ethtype(app_info_bitmap);

	return !!(ethtype && (proto_id == ECORE_ETH_TYPE_DEFAULT));
}