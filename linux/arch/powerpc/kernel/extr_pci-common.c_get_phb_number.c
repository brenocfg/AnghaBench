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
typedef  int u64 ;
typedef  int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_PHBS ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 int of_property_read_u64 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  phb_bitmap ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_phb_number(struct device_node *dn)
{
	int ret, phb_id = -1;
	u32 prop_32;
	u64 prop;

	/*
	 * Try fixed PHB numbering first, by checking archs and reading
	 * the respective device-tree properties. Firstly, try powernv by
	 * reading "ibm,opal-phbid", only present in OPAL environment.
	 */
	ret = of_property_read_u64(dn, "ibm,opal-phbid", &prop);
	if (ret) {
		ret = of_property_read_u32_index(dn, "reg", 1, &prop_32);
		prop = prop_32;
	}

	if (!ret)
		phb_id = (int)(prop & (MAX_PHBS - 1));

	/* We need to be sure to not use the same PHB number twice. */
	if ((phb_id >= 0) && !test_and_set_bit(phb_id, phb_bitmap))
		return phb_id;

	/*
	 * If not pseries nor powernv, or if fixed PHB numbering tried to add
	 * the same PHB number twice, then fallback to dynamic PHB numbering.
	 */
	phb_id = find_first_zero_bit(phb_bitmap, MAX_PHBS);
	BUG_ON(phb_id >= MAX_PHBS);
	set_bit(phb_id, phb_bitmap);

	return phb_id;
}