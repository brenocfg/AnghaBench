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
struct wpa_global {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_supplicant_terminate_proc (struct wpa_global*) ; 

__attribute__((used)) static void wpa_supplicant_terminate(int sig, void *signal_ctx)
{
	struct wpa_global *global = signal_ctx;
	wpa_supplicant_terminate_proc(global);
}