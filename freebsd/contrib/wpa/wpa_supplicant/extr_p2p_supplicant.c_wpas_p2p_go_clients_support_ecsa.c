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
struct wpa_supplicant {TYPE_1__* ap_iface; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_for_each_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wpas_sta_check_ecsa ; 

__attribute__((used)) static int wpas_p2p_go_clients_support_ecsa(struct wpa_supplicant *wpa_s)
{
	int ecsa_support = 1;

	ap_for_each_sta(wpa_s->ap_iface->bss[0], wpas_sta_check_ecsa,
			&ecsa_support);

	return ecsa_support;
}