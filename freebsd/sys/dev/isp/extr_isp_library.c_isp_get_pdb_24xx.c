#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pdb_reserved1; int /*<<< orphan*/ * pdb_portname; int /*<<< orphan*/ * pdb_nodename; int /*<<< orphan*/  pdb_prli_svc3; int /*<<< orphan*/  pdb_prli_svc0; int /*<<< orphan*/  pdb_reserved0; int /*<<< orphan*/  pdb_rcv_dsize; int /*<<< orphan*/  pdb_handle; int /*<<< orphan*/  pdb_retry_timer; int /*<<< orphan*/ * pdb_portid_bits; int /*<<< orphan*/ * pdb_hardaddr_bits; int /*<<< orphan*/  pdb_laststate; int /*<<< orphan*/  pdb_curstate; int /*<<< orphan*/  pdb_flags; } ;
typedef  TYPE_1__ isp_pdb_24xx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXGET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOXGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
isp_get_pdb_24xx(ispsoftc_t *isp, isp_pdb_24xx_t *src, isp_pdb_24xx_t *dst)
{
	int i;
	ISP_IOXGET_16(isp, &src->pdb_flags, dst->pdb_flags);
        ISP_IOXGET_8(isp, &src->pdb_curstate, dst->pdb_curstate);
        ISP_IOXGET_8(isp, &src->pdb_laststate, dst->pdb_laststate);
	for (i = 0; i < 4; i++) {
		ISP_IOXGET_8(isp, &src->pdb_hardaddr_bits[i], dst->pdb_hardaddr_bits[i]);
	}
	for (i = 0; i < 4; i++) {
		ISP_IOXGET_8(isp, &src->pdb_portid_bits[i], dst->pdb_portid_bits[i]);
	}
	ISP_IOXGET_16(isp, &src->pdb_retry_timer, dst->pdb_retry_timer);
	ISP_IOXGET_16(isp, &src->pdb_handle, dst->pdb_handle);
	ISP_IOXGET_16(isp, &src->pdb_rcv_dsize, dst->pdb_rcv_dsize);
	ISP_IOXGET_16(isp, &src->pdb_reserved0, dst->pdb_reserved0);
	ISP_IOXGET_16(isp, &src->pdb_prli_svc0, dst->pdb_prli_svc0);
	ISP_IOXGET_16(isp, &src->pdb_prli_svc3, dst->pdb_prli_svc3);
	for (i = 0; i < 8; i++) {
		ISP_IOXGET_8(isp, &src->pdb_nodename[i], dst->pdb_nodename[i]);
	}
	for (i = 0; i < 8; i++) {
		ISP_IOXGET_8(isp, &src->pdb_portname[i], dst->pdb_portname[i]);
	}
	for (i = 0; i < 24; i++) {
		ISP_IOXGET_8(isp, &src->pdb_reserved1[i], dst->pdb_reserved1[i]);
	}
}