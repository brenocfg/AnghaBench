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
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*) ; 
 int /*<<< orphan*/  IB_ATTR_LINEARFORWTBL ; 
 int IB_SMP_DATA_SIZE ; 
 int* buf ; 
 int mirror_dlid ; 
 int mirror_dport ; 
 int /*<<< orphan*/  smp_query_via (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 

int get_out_port(ib_portid_t* portid)
{
	int block;
	int offset;

	if (mirror_dlid) {
		block = mirror_dlid / IB_SMP_DATA_SIZE;
		offset = mirror_dlid - block * IB_SMP_DATA_SIZE;
		/* get out port from lft */
		if (!smp_query_via(buf, portid, IB_ATTR_LINEARFORWTBL, block, 0, srcport))
			IBEXIT("linear forwarding table get failed");
		block = mirror_dlid / IB_SMP_DATA_SIZE;
		offset = mirror_dlid - block * IB_SMP_DATA_SIZE;
		return buf[offset];
	}
	else
		return mirror_dport;
}