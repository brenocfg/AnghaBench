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
struct wps_registrar {int /*<<< orphan*/  p2p_dev_addr; } ;
struct wps_data {int /*<<< orphan*/  p2p_dev_addr; TYPE_1__* wps; } ;
struct TYPE_2__ {struct wps_registrar* registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wps_registrar_skip_overlap(struct wps_data *wps)
{
#ifdef CONFIG_P2P
	struct wps_registrar *reg = wps->wps->registrar;

	if (is_zero_ether_addr(reg->p2p_dev_addr))
		return 0; /* no specific Enrollee selected */

	if (os_memcmp(reg->p2p_dev_addr, wps->p2p_dev_addr, ETH_ALEN) == 0) {
		wpa_printf(MSG_DEBUG, "WPS: Skip PBC overlap due to selected "
			   "Enrollee match");
		return 1;
	}
#endif /* CONFIG_P2P */
	return 0;
}