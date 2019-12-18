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

/* Variables and functions */
 int /*<<< orphan*/  wpa_supplicant_cancel_auth_timeout (void*) ; 

__attribute__((used)) static void _wpa_supplicant_cancel_auth_timeout(void *wpa_s)
{
	wpa_supplicant_cancel_auth_timeout(wpa_s);
}