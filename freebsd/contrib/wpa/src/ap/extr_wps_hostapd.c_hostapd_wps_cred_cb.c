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
struct wps_credential {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hapd_wps_cred_cb ; 
 int hostapd_wps_for_each (struct hostapd_data*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int hostapd_wps_cred_cb(void *ctx, const struct wps_credential *cred)
{
	struct hostapd_data *hapd = ctx;
	return hostapd_wps_for_each(hapd, hapd_wps_cred_cb, (void *) cred);
}