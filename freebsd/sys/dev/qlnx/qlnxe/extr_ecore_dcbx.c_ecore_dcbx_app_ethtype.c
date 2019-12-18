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

/* Variables and functions */
 int /*<<< orphan*/  DCBX_APP_SF ; 
 scalar_t__ DCBX_APP_SF_ETHTYPE ; 
 scalar_t__ GET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ecore_dcbx_app_ethtype(u32 app_info_bitmap)
{
	return !!(GET_MFW_FIELD(app_info_bitmap, DCBX_APP_SF) ==
		  DCBX_APP_SF_ETHTYPE);
}