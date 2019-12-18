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
struct wpa_radio_work {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int radio_work_is_scan(struct wpa_radio_work *work)
{
	return os_strcmp(work->type, "scan") == 0 ||
		os_strcmp(work->type, "p2p-scan") == 0;
}