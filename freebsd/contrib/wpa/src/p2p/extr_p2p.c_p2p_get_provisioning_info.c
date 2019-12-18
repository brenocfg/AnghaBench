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
typedef  int /*<<< orphan*/  u16 ;
struct p2p_device {int /*<<< orphan*/  wps_prov_info; } ;
struct p2p_data {int dummy; } ;

/* Variables and functions */
 struct p2p_device* p2p_get_device (struct p2p_data*,int /*<<< orphan*/  const*) ; 

u16 p2p_get_provisioning_info(struct p2p_data *p2p, const u8 *addr)
{
	struct p2p_device *dev = NULL;

	if (!addr || !p2p)
		return 0;

	dev = p2p_get_device(p2p, addr);
	if (dev)
		return dev->wps_prov_info;
	else
		return 0;
}