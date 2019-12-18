#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct TYPE_9__ {int isp_confopts; } ;
typedef  TYPE_1__ ispsoftc_t ;
struct TYPE_10__ {int isp_wwpn_nvram; int isp_wwnn_nvram; void* isp_zfwoptions; void* isp_xfwoptions; int /*<<< orphan*/  isp_fwoptions; int /*<<< orphan*/  isp_loopid; int /*<<< orphan*/  isp_retry_count; int /*<<< orphan*/  isp_retry_delay; int /*<<< orphan*/  isp_maxalloc; } ;
typedef  TYPE_2__ fcparam ;
typedef  int /*<<< orphan*/  DEFAULT_FRAMESIZE ;
typedef  int /*<<< orphan*/  DEFAULT_EXEC_THROTTLE ;

/* Variables and functions */
 TYPE_2__* FCPARAM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP2100_NVRAM_EXECUTION_THROTTLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP2100_NVRAM_HARDLOOPID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP2100_NVRAM_MAXFRAMELENGTH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP2100_NVRAM_MAXIOCBALLOCATION (int /*<<< orphan*/ *) ; 
 int ISP2100_NVRAM_NODE_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP2100_NVRAM_OPTIONS (int /*<<< orphan*/ *) ; 
 int ISP2100_NVRAM_PORT_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP2100_NVRAM_RETRY_COUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP2100_NVRAM_RETRY_DELAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP2100_NVRAM_TOV (int /*<<< orphan*/ *) ; 
 void* ISP2100_XFW_OPTIONS (int /*<<< orphan*/ *) ; 
 void* ISP2100_ZFW_OPTIONS (int /*<<< orphan*/ *) ; 
 int ISP_CFG_OWNEXCTHROTTLE ; 
 int ISP_CFG_OWNFSZ ; 
 int ISP_CFG_OWNLOOPID ; 
 int /*<<< orphan*/  ISP_LOGCONFIG ; 
 int /*<<< orphan*/  ISP_LOGDEBUG0 ; 
 scalar_t__ IS_2200 (TYPE_1__*) ; 
 scalar_t__ IS_23XX (TYPE_1__*) ; 
 int /*<<< orphan*/  isp_prt (TYPE_1__*,int /*<<< orphan*/ ,char*,void*,void*,...) ; 

__attribute__((used)) static void
isp_parse_nvram_2100(ispsoftc_t *isp, uint8_t *nvram_data)
{
	fcparam *fcp = FCPARAM(isp, 0);
	uint64_t wwn;

	/*
	 * There is NVRAM storage for both Port and Node entities-
	 * but the Node entity appears to be unused on all the cards
	 * I can find. However, we should account for this being set
	 * at some point in the future.
	 *
	 * Qlogic WWNs have an NAA of 2, but usually nothing shows up in
	 * bits 48..60. In the case of the 2202, it appears that they do
	 * use bit 48 to distinguish between the two instances on the card.
	 * The 2204, which I've never seen, *probably* extends this method.
	 */
	wwn = ISP2100_NVRAM_PORT_NAME(nvram_data);
	if (wwn) {
		isp_prt(isp, ISP_LOGCONFIG, "NVRAM Port WWN 0x%08x%08x",
		    (uint32_t) (wwn >> 32), (uint32_t) (wwn));
		if ((wwn >> 60) == 0) {
			wwn |= (((uint64_t) 2)<< 60);
		}
	}
	fcp->isp_wwpn_nvram = wwn;
	if (IS_2200(isp) || IS_23XX(isp)) {
		wwn = ISP2100_NVRAM_NODE_NAME(nvram_data);
		if (wwn) {
			isp_prt(isp, ISP_LOGCONFIG, "NVRAM Node WWN 0x%08x%08x",
			    (uint32_t) (wwn >> 32),
			    (uint32_t) (wwn));
			if ((wwn >> 60) == 0) {
				wwn |= (((uint64_t) 2)<< 60);
			}
		} else {
			wwn = fcp->isp_wwpn_nvram & ~((uint64_t) 0xfff << 48);
		}
	} else {
		wwn &= ~((uint64_t) 0xfff << 48);
	}
	fcp->isp_wwnn_nvram = wwn;

	fcp->isp_maxalloc = ISP2100_NVRAM_MAXIOCBALLOCATION(nvram_data);
	if ((isp->isp_confopts & ISP_CFG_OWNFSZ) == 0) {
		DEFAULT_FRAMESIZE(isp) =
		    ISP2100_NVRAM_MAXFRAMELENGTH(nvram_data);
	}
	fcp->isp_retry_delay = ISP2100_NVRAM_RETRY_DELAY(nvram_data);
	fcp->isp_retry_count = ISP2100_NVRAM_RETRY_COUNT(nvram_data);
	if ((isp->isp_confopts & ISP_CFG_OWNLOOPID) == 0) {
		fcp->isp_loopid = ISP2100_NVRAM_HARDLOOPID(nvram_data);
	}
	if ((isp->isp_confopts & ISP_CFG_OWNEXCTHROTTLE) == 0) {
		DEFAULT_EXEC_THROTTLE(isp) =
			ISP2100_NVRAM_EXECUTION_THROTTLE(nvram_data);
	}
	fcp->isp_fwoptions = ISP2100_NVRAM_OPTIONS(nvram_data);
	isp_prt(isp, ISP_LOGDEBUG0,
	    "NVRAM 0x%08x%08x 0x%08x%08x maxalloc %d maxframelen %d",
	    (uint32_t) (fcp->isp_wwnn_nvram >> 32),
	    (uint32_t) fcp->isp_wwnn_nvram,
	    (uint32_t) (fcp->isp_wwpn_nvram >> 32),
	    (uint32_t) fcp->isp_wwpn_nvram,
	    ISP2100_NVRAM_MAXIOCBALLOCATION(nvram_data),
	    ISP2100_NVRAM_MAXFRAMELENGTH(nvram_data));
	isp_prt(isp, ISP_LOGDEBUG0,
	    "execthrottle %d fwoptions 0x%x hardloop %d tov %d",
	    ISP2100_NVRAM_EXECUTION_THROTTLE(nvram_data),
	    ISP2100_NVRAM_OPTIONS(nvram_data),
	    ISP2100_NVRAM_HARDLOOPID(nvram_data),
	    ISP2100_NVRAM_TOV(nvram_data));
	fcp->isp_xfwoptions = ISP2100_XFW_OPTIONS(nvram_data);
	fcp->isp_zfwoptions = ISP2100_ZFW_OPTIONS(nvram_data);
	isp_prt(isp, ISP_LOGDEBUG0, "xfwoptions 0x%x zfw options 0x%x",
	    ISP2100_XFW_OPTIONS(nvram_data), ISP2100_ZFW_OPTIONS(nvram_data));
}