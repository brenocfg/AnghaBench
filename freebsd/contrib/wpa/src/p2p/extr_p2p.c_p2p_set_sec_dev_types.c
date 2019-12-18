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
typedef  int /*<<< orphan*/  u8 ;
struct p2p_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {size_t num_sec_dev_types; int /*<<< orphan*/  sec_dev_type; } ;

/* Variables and functions */
 size_t P2P_SEC_DEVICE_TYPES ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,size_t) ; 

int p2p_set_sec_dev_types(struct p2p_data *p2p, const u8 dev_types[][8],
			  size_t num_dev_types)
{
	if (num_dev_types > P2P_SEC_DEVICE_TYPES)
		num_dev_types = P2P_SEC_DEVICE_TYPES;
	p2p->cfg->num_sec_dev_types = num_dev_types;
	os_memcpy(p2p->cfg->sec_dev_type, dev_types, num_dev_types * 8);
	return 0;
}