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
struct wpa_scan_results {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  interworking_start_fetch_anqp (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void interworking_scan_res_handler(struct wpa_supplicant *wpa_s,
					  struct wpa_scan_results *scan_res)
{
	wpa_msg(wpa_s, MSG_DEBUG,
		"Interworking: Scan results available - start ANQP fetch");
	interworking_start_fetch_anqp(wpa_s);
}