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
typedef  int u8 ;
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_RSS_CONFIG_VRT ; 
 int /*<<< orphan*/  A_TP_RSS_SECRET_KEY0 ; 
 scalar_t__ CHELSIO_T5 ; 
 int F_KEYEXTEND ; 
 int F_KEYWREN ; 
 int G_KEYMODE (int) ; 
 int V_KEYWRADDR (int) ; 
 int V_KEYWRADDRX (int) ; 
 int V_T6_VFWRADDR (int) ; 
 scalar_t__ chip_id (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_tp_pio_write (struct adapter*,int const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t4_write_rss_key(struct adapter *adap, const u32 *key, int idx,
		      bool sleep_ok)
{
	u8 rss_key_addr_cnt = 16;
	u32 vrt = t4_read_reg(adap, A_TP_RSS_CONFIG_VRT);

	/*
	 * T6 and later: for KeyMode 3 (per-vf and per-vf scramble),
	 * allows access to key addresses 16-63 by using KeyWrAddrX
	 * as index[5:4](upper 2) into key table
	 */
	if ((chip_id(adap) > CHELSIO_T5) &&
	    (vrt & F_KEYEXTEND) && (G_KEYMODE(vrt) == 3))
		rss_key_addr_cnt = 32;

	t4_tp_pio_write(adap, key, 10, A_TP_RSS_SECRET_KEY0, sleep_ok);

	if (idx >= 0 && idx < rss_key_addr_cnt) {
		if (rss_key_addr_cnt > 16)
			t4_write_reg(adap, A_TP_RSS_CONFIG_VRT,
				     vrt | V_KEYWRADDRX(idx >> 4) |
				     V_T6_VFWRADDR(idx) | F_KEYWREN);
		else
			t4_write_reg(adap, A_TP_RSS_CONFIG_VRT,
				     vrt| V_KEYWRADDR(idx) | F_KEYWREN);
	}
}