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
struct wpa_ctrl_dst {struct wpa_ctrl_dst* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct wpa_ctrl_dst*) ; 

__attribute__((used)) static void wpas_ctrl_iface_free_dst(struct wpa_ctrl_dst *dst)
{
	struct wpa_ctrl_dst *prev;

	while (dst) {
		prev = dst;
		dst = dst->next;
		os_free(prev);
	}
}