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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int CL_NTOH32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBEXIT (char*) ; 
 int /*<<< orphan*/  IB_ATTR_PORT_INFO ; 
 int /*<<< orphan*/  IB_PORT_CAPMASK_F ; 
 int /*<<< orphan*/  IB_PORT_CAP_HAS_EXT_SPEEDS ; 
 int IB_SMP_DATA_SIZE ; 
 int mad_get_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_query_via (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 

__attribute__((used)) static int get_port_info(ib_portid_t * dest, uint8_t * data, int portnum,
			 int is_switch)
{
	uint8_t smp[IB_SMP_DATA_SIZE];
	uint8_t *info;
	int cap_mask;

	if (is_switch) {
		if (!smp_query_via(smp, dest, IB_ATTR_PORT_INFO, 0, 0, srcport))
			IBEXIT("smp query port 0 portinfo failed");
		info = smp;
	} else
		info = data;

	if (!smp_query_via(data, dest, IB_ATTR_PORT_INFO, portnum, 0, srcport))
		IBEXIT("smp query portinfo failed");
	cap_mask = mad_get_field(info, 0, IB_PORT_CAPMASK_F);
	return (cap_mask & CL_NTOH32(IB_PORT_CAP_HAS_EXT_SPEEDS));
}