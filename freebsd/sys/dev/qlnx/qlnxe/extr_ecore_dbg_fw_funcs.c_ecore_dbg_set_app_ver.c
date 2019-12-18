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
typedef  scalar_t__ u32 ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int DBG_STATUS_OK ; 
 int DBG_STATUS_UNSUPPORTED_APP_VERSION ; 
 scalar_t__ TOOLS_VERSION ; 
 scalar_t__ s_app_ver ; 

enum dbg_status ecore_dbg_set_app_ver(u32 ver)
{
	if (ver < TOOLS_VERSION)
		return DBG_STATUS_UNSUPPORTED_APP_VERSION;

	s_app_ver = ver;

	return DBG_STATUS_OK;
}