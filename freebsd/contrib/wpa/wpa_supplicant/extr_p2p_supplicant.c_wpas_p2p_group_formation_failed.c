#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {TYPE_1__* global; int /*<<< orphan*/  p2pdev; } ;
struct TYPE_2__ {scalar_t__ p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_group_formation_failed (scalar_t__) ; 
 int /*<<< orphan*/  wpas_group_formation_completed (struct wpa_supplicant*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpas_p2p_group_formation_timeout ; 

__attribute__((used)) static void wpas_p2p_group_formation_failed(struct wpa_supplicant *wpa_s,
					    int already_deleted)
{
	eloop_cancel_timeout(wpas_p2p_group_formation_timeout,
			     wpa_s->p2pdev, NULL);
	if (wpa_s->global->p2p)
		p2p_group_formation_failed(wpa_s->global->p2p);
	wpas_group_formation_completed(wpa_s, 0, already_deleted);
}