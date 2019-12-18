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

/* Variables and functions */

__attribute__((used)) static char *
ixl_phy_type_string(u32 bit_pos, bool ext)
{
	static char * phy_types_str[32] = {
		"SGMII",
		"1000BASE-KX",
		"10GBASE-KX4",
		"10GBASE-KR",
		"40GBASE-KR4",
		"XAUI",
		"XFI",
		"SFI",
		"XLAUI",
		"XLPPI",
		"40GBASE-CR4",
		"10GBASE-CR1",
		"SFP+ Active DA",
		"QSFP+ Active DA",
		"Reserved (14)",
		"Reserved (15)",
		"Reserved (16)",
		"100BASE-TX",
		"1000BASE-T",
		"10GBASE-T",
		"10GBASE-SR",
		"10GBASE-LR",
		"10GBASE-SFP+Cu",
		"10GBASE-CR1",
		"40GBASE-CR4",
		"40GBASE-SR4",
		"40GBASE-LR4",
		"1000BASE-SX",
		"1000BASE-LX",
		"1000BASE-T Optical",
		"20GBASE-KR2",
		"Reserved (31)"
	};
	static char * ext_phy_types_str[8] = {
		"25GBASE-KR",
		"25GBASE-CR",
		"25GBASE-SR",
		"25GBASE-LR",
		"25GBASE-AOC",
		"25GBASE-ACC",
		"Reserved (6)",
		"Reserved (7)"
	};

	if (ext && bit_pos > 7) return "Invalid_Ext";
	if (bit_pos > 31) return "Invalid";

	return (ext) ? ext_phy_types_str[bit_pos] : phy_types_str[bit_pos];
}