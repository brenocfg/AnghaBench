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
typedef  int u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int RSS_IND_TABLE_BASE_ADDR ; 
 int RSS_IND_TABLE_ENTRY_PER_LINE ; 
 int RSS_IND_TABLE_VPORT_SIZE ; 
 scalar_t__ RSS_REG_RSS_RAM_ADDR ; 
 scalar_t__ RSS_REG_RSS_RAM_DATA ; 
 scalar_t__ RSS_REG_RSS_RAM_MASK ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,int) ; 

void ecore_update_eth_rss_ind_table_entry(struct ecore_hwfn * p_hwfn,
    struct ecore_ptt *p_ptt,
    u8 rss_id,
    u8 ind_table_index,
    u16 ind_table_value)
{
    u32 cnt, rss_addr;
    u32 * reg_val;
    u16 rss_ind_entry[RSS_IND_TABLE_ENTRY_PER_LINE];
    u16 rss_ind_mask [RSS_IND_TABLE_ENTRY_PER_LINE];

    /* get entry address */
    rss_addr =  RSS_IND_TABLE_BASE_ADDR +
                RSS_IND_TABLE_VPORT_SIZE * rss_id +
                ind_table_index/RSS_IND_TABLE_ENTRY_PER_LINE;

    /* prepare update command */
    ind_table_index %= RSS_IND_TABLE_ENTRY_PER_LINE;

    for (cnt = 0; cnt < RSS_IND_TABLE_ENTRY_PER_LINE; cnt ++)
    {
        if (cnt == ind_table_index)
        {
            rss_ind_entry[cnt] = ind_table_value;
            rss_ind_mask[cnt]  = 0xFFFF;
        }
        else
        {
            rss_ind_entry[cnt] = 0;
            rss_ind_mask[cnt]  = 0;
        }
    }

    /* Update entry in HW*/
    ecore_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_ADDR, rss_addr);

    reg_val = (u32*)rss_ind_mask;
    ecore_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_MASK, reg_val[0]);
    ecore_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_MASK + 4, reg_val[1]);
    ecore_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_MASK + 8, reg_val[2]);
    ecore_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_MASK + 12, reg_val[3]);

    reg_val = (u32*)rss_ind_entry;
    ecore_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_DATA, reg_val[0]);
    ecore_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_DATA + 4, reg_val[1]);
    ecore_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_DATA + 8, reg_val[2]);
    ecore_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_DATA + 12, reg_val[3]);
}