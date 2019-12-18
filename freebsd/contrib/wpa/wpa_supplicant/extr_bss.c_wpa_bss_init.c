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
struct wpa_supplicant {int /*<<< orphan*/  bss_id; int /*<<< orphan*/  bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 

int wpa_bss_init(struct wpa_supplicant *wpa_s)
{
	dl_list_init(&wpa_s->bss);
	dl_list_init(&wpa_s->bss_id);
	return 0;
}