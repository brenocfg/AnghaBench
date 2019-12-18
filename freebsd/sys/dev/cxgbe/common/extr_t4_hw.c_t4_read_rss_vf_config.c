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
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_RSS_CONFIG_VRT ; 
 int /*<<< orphan*/  A_TP_RSS_VFH_CONFIG ; 
 int /*<<< orphan*/  A_TP_RSS_VFL_CONFIG ; 
 scalar_t__ CHELSIO_T5 ; 
 int F_KEYWREN ; 
 int F_VFRDEN ; 
 int F_VFRDRG ; 
 int F_VFWREN ; 
 unsigned int M_T6_VFWRADDR ; 
 unsigned int M_VFWRADDR ; 
 int V_T6_VFWRADDR (unsigned int) ; 
 int V_VFWRADDR (unsigned int) ; 
 scalar_t__ chip_id (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_tp_pio_read (struct adapter*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t4_read_rss_vf_config(struct adapter *adapter, unsigned int index,
			   u32 *vfl, u32 *vfh, bool sleep_ok)
{
	u32 vrt, mask, data;

	if (chip_id(adapter) <= CHELSIO_T5) {
		mask = V_VFWRADDR(M_VFWRADDR);
		data = V_VFWRADDR(index);
	} else {
		 mask =  V_T6_VFWRADDR(M_T6_VFWRADDR);
		 data = V_T6_VFWRADDR(index);
	}
	/*
	 * Request that the index'th VF Table values be read into VFL/VFH.
	 */
	vrt = t4_read_reg(adapter, A_TP_RSS_CONFIG_VRT);
	vrt &= ~(F_VFRDRG | F_VFWREN | F_KEYWREN | mask);
	vrt |= data | F_VFRDEN;
	t4_write_reg(adapter, A_TP_RSS_CONFIG_VRT, vrt);

	/*
	 * Grab the VFL/VFH values ...
	 */
	t4_tp_pio_read(adapter, vfl, 1, A_TP_RSS_VFL_CONFIG, sleep_ok);
	t4_tp_pio_read(adapter, vfh, 1, A_TP_RSS_VFH_CONFIG, sleep_ok);
}