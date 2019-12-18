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
struct TYPE_2__ {int timet; } ;
union nps_pkt_slc_int_levels {scalar_t__ value; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_PKT_SLC_INT_LEVELSX (int) ; 
 int /*<<< orphan*/  enable_pkt_solicit_port (struct nitrox_device*,int) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  reset_pkt_solicit_port (struct nitrox_device*,int) ; 

__attribute__((used)) static void config_pkt_solicit_port(struct nitrox_device *ndev, int port)
{
	union nps_pkt_slc_int_levels pkt_slc_int;
	u64 offset;

	reset_pkt_solicit_port(ndev, port);

	/* step 4: configure interrupt levels */
	offset = NPS_PKT_SLC_INT_LEVELSX(port);
	pkt_slc_int.value = 0;
	/* time interrupt threshold */
	pkt_slc_int.s.timet = 0x3fffff;
	nitrox_write_csr(ndev, offset, pkt_slc_int.value);

	/* enable the solicit port */
	enable_pkt_solicit_port(ndev, port);
}