#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_3__ {int /*<<< orphan*/ * portname; int /*<<< orphan*/  portid; } ;
typedef  TYPE_1__ isp_pdb_t ;

/* Variables and functions */
 scalar_t__ ISP_CAP_2KLOGIN (int /*<<< orphan*/ *) ; 
 int ISP_LOGINFO ; 
 int ISP_LOG_SANCFG ; 
 scalar_t__ NPH_MAX ; 
 scalar_t__ NPH_MAX_2K ; 
 scalar_t__ isp_getpdb (int /*<<< orphan*/ *,int,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int,char*,int,...) ; 

__attribute__((used)) static void
isp_dump_chip_portdb(ispsoftc_t *isp, int chan)
{
	isp_pdb_t pdb;
	uint16_t lim, nphdl;

	isp_prt(isp, ISP_LOG_SANCFG|ISP_LOGINFO, "Chan %d chip port dump", chan);
	if (ISP_CAP_2KLOGIN(isp)) {
		lim = NPH_MAX_2K;
	} else {
		lim = NPH_MAX;
	}
	for (nphdl = 0; nphdl != lim; nphdl++) {
		if (isp_getpdb(isp, chan, nphdl, &pdb)) {
			continue;
		}
		isp_prt(isp, ISP_LOG_SANCFG|ISP_LOGINFO, "Chan %d Handle 0x%04x "
		    "PortID 0x%06x WWPN 0x%02x%02x%02x%02x%02x%02x%02x%02x",
		    chan, nphdl, pdb.portid, pdb.portname[0], pdb.portname[1],
		    pdb.portname[2], pdb.portname[3], pdb.portname[4],
		    pdb.portname[5], pdb.portname[6], pdb.portname[7]);
	}
}