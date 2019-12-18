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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int wpas_p2p_in_progress (struct wpa_supplicant*) ; 

__attribute__((used)) static int _wpas_p2p_in_progress(void *ctx)
{
	struct wpa_supplicant *wpa_s = ctx;
	return wpas_p2p_in_progress(wpa_s);
}