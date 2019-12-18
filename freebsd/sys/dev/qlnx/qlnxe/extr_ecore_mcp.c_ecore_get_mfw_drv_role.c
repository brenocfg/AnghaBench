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
typedef  enum ecore_drv_role { ____Placeholder_ecore_drv_role } ecore_drv_role ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_ROLE_KDUMP ; 
 int /*<<< orphan*/  DRV_ROLE_OS ; 
#define  ECORE_DRV_ROLE_KDUMP 129 
#define  ECORE_DRV_ROLE_OS 128 

__attribute__((used)) static void ecore_get_mfw_drv_role(enum ecore_drv_role drv_role,
				   u8 *p_mfw_drv_role)
{
	switch (drv_role) {
	case ECORE_DRV_ROLE_OS:
		*p_mfw_drv_role = DRV_ROLE_OS;
		break;
	case ECORE_DRV_ROLE_KDUMP:
		*p_mfw_drv_role = DRV_ROLE_KDUMP;
		break;
	}
}