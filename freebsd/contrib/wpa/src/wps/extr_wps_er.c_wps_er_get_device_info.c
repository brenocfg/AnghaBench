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
struct wps_er_ap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wps_er_ap_get_m1 ; 
 int /*<<< orphan*/  wps_er_send_get_device_info (struct wps_er_ap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wps_er_get_device_info(struct wps_er_ap *ap)
{
	wps_er_send_get_device_info(ap, wps_er_ap_get_m1);
}