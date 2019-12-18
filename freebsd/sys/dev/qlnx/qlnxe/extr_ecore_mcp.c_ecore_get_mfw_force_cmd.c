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
typedef  enum ecore_load_req_force { ____Placeholder_ecore_load_req_force } ecore_load_req_force ;

/* Variables and functions */
#define  ECORE_LOAD_REQ_FORCE_ALL 130 
#define  ECORE_LOAD_REQ_FORCE_NONE 129 
#define  ECORE_LOAD_REQ_FORCE_PF 128 
 int /*<<< orphan*/  LOAD_REQ_FORCE_ALL ; 
 int /*<<< orphan*/  LOAD_REQ_FORCE_NONE ; 
 int /*<<< orphan*/  LOAD_REQ_FORCE_PF ; 

__attribute__((used)) static void ecore_get_mfw_force_cmd(enum ecore_load_req_force force_cmd,
				    u8 *p_mfw_force_cmd)
{
	switch (force_cmd) {
	case ECORE_LOAD_REQ_FORCE_NONE:
		*p_mfw_force_cmd = LOAD_REQ_FORCE_NONE;
		break;
	case ECORE_LOAD_REQ_FORCE_PF:
		*p_mfw_force_cmd = LOAD_REQ_FORCE_PF;
		break;
	case ECORE_LOAD_REQ_FORCE_ALL:
		*p_mfw_force_cmd = LOAD_REQ_FORCE_ALL;
		break;
	}
}