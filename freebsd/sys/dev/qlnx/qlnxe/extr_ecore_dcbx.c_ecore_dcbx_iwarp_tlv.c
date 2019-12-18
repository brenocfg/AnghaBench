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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct ecore_hwfn {TYPE_1__* p_dcbx_info; } ;
struct TYPE_2__ {scalar_t__ iwarp_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCBX_APP_SF_IEEE_TCP_PORT ; 
 int ecore_dcbx_app_port (int /*<<< orphan*/ ) ; 
 int ecore_dcbx_ieee_app_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ecore_dcbx_iwarp_tlv(struct ecore_hwfn *p_hwfn, u32 app_info_bitmap,
				 u16 proto_id, bool ieee)
{
	bool port;

	if (!p_hwfn->p_dcbx_info->iwarp_port)
		return false;

	if (ieee)
		port = ecore_dcbx_ieee_app_port(app_info_bitmap,
						DCBX_APP_SF_IEEE_TCP_PORT);
	else
		port = ecore_dcbx_app_port(app_info_bitmap);

	return !!(port && (proto_id == p_hwfn->p_dcbx_info->iwarp_port));
}