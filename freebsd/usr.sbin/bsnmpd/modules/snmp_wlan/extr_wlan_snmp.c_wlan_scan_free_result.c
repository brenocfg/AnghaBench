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
struct wlan_scan_result {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct wlan_scan_result*) ; 

void
wlan_scan_free_result(struct wlan_scan_result *sr)
{
	free(sr);
}