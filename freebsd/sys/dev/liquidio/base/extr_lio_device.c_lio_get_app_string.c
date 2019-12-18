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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ LIO_DRV_APP_END ; 
 scalar_t__ LIO_DRV_APP_START ; 
 scalar_t__ LIO_DRV_INVALID_APP ; 
 char** lio_app_str ; 

__attribute__((used)) static char *
lio_get_app_string(uint32_t app_mode)
{

	if (app_mode <= LIO_DRV_APP_END)
		return (lio_app_str[app_mode - LIO_DRV_APP_START]);

	return (lio_app_str[LIO_DRV_INVALID_APP - LIO_DRV_APP_START]);
}