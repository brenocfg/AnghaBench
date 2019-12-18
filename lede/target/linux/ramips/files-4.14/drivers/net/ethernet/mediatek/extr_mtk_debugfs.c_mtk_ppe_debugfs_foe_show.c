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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vlan2; int /*<<< orphan*/  vlan1; int /*<<< orphan*/  info_blk2; int /*<<< orphan*/  info_blk1; int /*<<< orphan*/  etype; int /*<<< orphan*/  new_dport; int /*<<< orphan*/  new_sport; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/  dmac_lo; int /*<<< orphan*/  dmac_hi; int /*<<< orphan*/  smac_lo; int /*<<< orphan*/  smac_hi; int /*<<< orphan*/  new_dip; int /*<<< orphan*/  new_sip; int /*<<< orphan*/  dip; int /*<<< orphan*/  sip; } ;
struct mtk_foe_entry {TYPE_1__ ipv4_hnapt; } ;
struct mtk_eth {struct mtk_foe_entry* foe_table; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ IS_IPV4_HNAPT (struct mtk_foe_entry*) ; 
 int MTK_PPE_ENTRY_CNT ; 
 struct mtk_eth* _eth ; 
 int /*<<< orphan*/  ei (struct mtk_foe_entry*,struct mtk_foe_entry*) ; 
 int /*<<< orphan*/  es (struct mtk_foe_entry*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt (struct mtk_foe_entry*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  swab16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_ppe_debugfs_foe_show(struct seq_file *m, void *private)
{
	struct mtk_eth *eth = _eth;
	struct mtk_foe_entry *entry, *end;
	int i = 0;

	entry = eth->foe_table;
	end = eth->foe_table + MTK_PPE_ENTRY_CNT;

	while (entry < end) {
		if (IS_IPV4_HNAPT(entry)) {
			__be32 saddr = htonl(entry->ipv4_hnapt.sip);
			__be32 daddr = htonl(entry->ipv4_hnapt.dip);
			__be32 nsaddr = htonl(entry->ipv4_hnapt.new_sip);
			__be32 ndaddr = htonl(entry->ipv4_hnapt.new_dip);
			unsigned char h_dest[ETH_ALEN];
			unsigned char h_source[ETH_ALEN];

			*((u32*) h_source) = swab32(entry->ipv4_hnapt.smac_hi);
			*((u16*) &h_source[4]) = swab16(entry->ipv4_hnapt.smac_lo);
			*((u32*) h_dest) = swab32(entry->ipv4_hnapt.dmac_hi);
			*((u16*) &h_dest[4]) = swab16(entry->ipv4_hnapt.dmac_lo);
			seq_printf(m,
				   "(%x)0x%05x|state=%s|type=%s|"
				   "%pI4:%d->%pI4:%d=>%pI4:%d->%pI4:%d|%pM=>%pM|"
				   "etype=0x%04x|info1=0x%x|info2=0x%x|"
				   "vlan1=%d|vlan2=%d\n",
				   i,
				   ei(entry, end), es(entry), pt(entry),
				   &saddr, entry->ipv4_hnapt.sport,
				   &daddr, entry->ipv4_hnapt.dport,
				   &nsaddr, entry->ipv4_hnapt.new_sport,
				   &ndaddr, entry->ipv4_hnapt.new_dport, h_source,
				   h_dest, ntohs(entry->ipv4_hnapt.etype),
				   entry->ipv4_hnapt.info_blk1,
				   entry->ipv4_hnapt.info_blk2,
				   entry->ipv4_hnapt.vlan1,
				   entry->ipv4_hnapt.vlan2);
		} else
			seq_printf(m, "0x%05x state=%s\n",
				   ei(entry, end), es(entry));
		entry++;
		i++;
	}

	return 0;
}