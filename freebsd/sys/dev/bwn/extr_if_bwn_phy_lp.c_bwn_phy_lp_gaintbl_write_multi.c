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
struct bwn_txgain_entry {int dummy; } ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwn_phy_lp_gaintbl_write (struct bwn_mac*,int,struct bwn_txgain_entry) ; 

__attribute__((used)) static void
bwn_phy_lp_gaintbl_write_multi(struct bwn_mac *mac, int offset, int count,
    struct bwn_txgain_entry *table)
{
	int i;

	for (i = offset; i < count; i++)
		bwn_phy_lp_gaintbl_write(mac, i, table[i]);
}