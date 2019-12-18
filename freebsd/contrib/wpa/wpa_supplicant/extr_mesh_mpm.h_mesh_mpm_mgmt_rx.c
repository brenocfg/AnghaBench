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
struct rx_mgmt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void mesh_mpm_mgmt_rx(struct wpa_supplicant *wpa_s,
				    struct rx_mgmt *rx_mgmt)
{
}