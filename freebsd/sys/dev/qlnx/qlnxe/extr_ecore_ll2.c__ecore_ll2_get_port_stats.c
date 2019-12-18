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
struct ecore_ptt {int dummy; } ;
struct ecore_ll2_stats {int /*<<< orphan*/  gsi_crcchksm_error; int /*<<< orphan*/  gsi_unsupported_pkt_typ; int /*<<< orphan*/  gsi_invalid_pkt_length; int /*<<< orphan*/  gsi_invalid_hdr; } ;
struct ecore_hwfn {int dummy; } ;
struct core_ll2_port_stats {int /*<<< orphan*/  gsi_crcchksm_error; int /*<<< orphan*/  gsi_unsupported_pkt_typ; int /*<<< orphan*/  gsi_invalid_pkt_length; int /*<<< orphan*/  gsi_invalid_hdr; } ;
typedef  int /*<<< orphan*/  port_stats ;

/* Variables and functions */
 scalar_t__ BAR0_MAP_REG_TSDM_RAM ; 
 scalar_t__ HILO_64_REGPAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFW_PORT (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct core_ll2_port_stats*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TSTORM_LL2_PORT_STAT_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_memcpy_from (struct ecore_hwfn*,struct ecore_ptt*,struct core_ll2_port_stats*,scalar_t__,int) ; 

__attribute__((used)) static void _ecore_ll2_get_port_stats(struct ecore_hwfn *p_hwfn,
				      struct ecore_ptt *p_ptt,
				      struct ecore_ll2_stats *p_stats)
{
	struct core_ll2_port_stats port_stats;

	OSAL_MEMSET(&port_stats, 0, sizeof(port_stats));
	ecore_memcpy_from(p_hwfn, p_ptt, &port_stats,
			  BAR0_MAP_REG_TSDM_RAM +
			  TSTORM_LL2_PORT_STAT_OFFSET(MFW_PORT(p_hwfn)),
			  sizeof(port_stats));

	p_stats->gsi_invalid_hdr +=
		HILO_64_REGPAIR(port_stats.gsi_invalid_hdr);
	p_stats->gsi_invalid_pkt_length +=
		HILO_64_REGPAIR(port_stats.gsi_invalid_pkt_length);
	p_stats->gsi_unsupported_pkt_typ +=
		HILO_64_REGPAIR(port_stats.gsi_unsupported_pkt_typ);
	p_stats->gsi_crcchksm_error +=
		HILO_64_REGPAIR(port_stats.gsi_crcchksm_error);
}