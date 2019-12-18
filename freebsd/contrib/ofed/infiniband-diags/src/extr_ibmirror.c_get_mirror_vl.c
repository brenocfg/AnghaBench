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
typedef  int /*<<< orphan*/  ib_slvl_table_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*) ; 
 int /*<<< orphan*/  IB_ATTR_SLVL_TABLE ; 
 scalar_t__ buf ; 
 int ib_slvl_table_get (int /*<<< orphan*/ *,int) ; 
 int mirror_sl ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  smp_query_via (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 

int get_mirror_vl(ib_portid_t* portid, int outport)
{
	ib_slvl_table_t * p_slvl_tbl;
	int portnum;
	int vl;

	/* hack; assume all sl2vl mappings are the same for any in port and outport */
	portnum = (1 << 8) | outport;

	/* get sl2vl mapping */
	if (!smp_query_via(buf, portid, IB_ATTR_SLVL_TABLE, portnum, 0, srcport))
		IBEXIT("slvl query failed");

	p_slvl_tbl = (ib_slvl_table_t *) buf;
	vl = ib_slvl_table_get(p_slvl_tbl, mirror_sl);
	printf("mirror_sl %d, mirror_vl %d\n", mirror_sl, vl);
	return vl;
}