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
typedef  void* u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_RSS_LKP_TABLE ; 
 int /*<<< orphan*/  A_TP_RSS_MAP_TABLE ; 
 int EAGAIN ; 
 int RSS_TABLE_SIZE ; 
 int t3_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int t3_read_rss(adapter_t *adapter, u8 *lkup, u16 *map)
{
	int i;
	u32 val;

	if (lkup)
		for (i = 0; i < RSS_TABLE_SIZE; ++i) {
			t3_write_reg(adapter, A_TP_RSS_LKP_TABLE,
				     0xffff0000 | i);
			val = t3_read_reg(adapter, A_TP_RSS_LKP_TABLE);
			if (!(val & 0x80000000))
				return -EAGAIN;
			*lkup++ = (u8)val;
			*lkup++ = (u8)(val >> 8);
		}

	if (map)
		for (i = 0; i < RSS_TABLE_SIZE; ++i) {
			t3_write_reg(adapter, A_TP_RSS_MAP_TABLE,
				     0xffff0000 | i);
			val = t3_read_reg(adapter, A_TP_RSS_MAP_TABLE);
			if (!(val & 0x80000000))
				return -EAGAIN;
			*map++ = (u16)val;
		}
	return 0;
}