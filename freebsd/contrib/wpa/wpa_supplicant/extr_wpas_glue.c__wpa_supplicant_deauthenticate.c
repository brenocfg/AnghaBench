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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_req_scan (void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _wpa_supplicant_deauthenticate(void *wpa_s, u16 reason_code)
{
	wpa_supplicant_deauthenticate(wpa_s, reason_code);
	/* Schedule a scan to make sure we continue looking for networks */
	wpa_supplicant_req_scan(wpa_s, 5, 0);
}