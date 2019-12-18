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
typedef  int /*<<< orphan*/  u8 ;
struct wps_registrar {int /*<<< orphan*/  p2p_dev_addr; scalar_t__ pbc; scalar_t__ selected_registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_registrar_remove_authorized_mac (struct wps_registrar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_registrar_selected_registrar_changed (struct wps_registrar*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wps_registrar_stop_pbc(struct wps_registrar *reg)
{
	reg->selected_registrar = 0;
	reg->pbc = 0;
	os_memset(reg->p2p_dev_addr, 0, ETH_ALEN);
	wps_registrar_remove_authorized_mac(reg,
					    (u8 *) "\xff\xff\xff\xff\xff\xff");
	wps_registrar_selected_registrar_changed(reg, 0);
}