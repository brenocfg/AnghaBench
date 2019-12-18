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
struct TYPE_4__ {int /*<<< orphan*/ * icb_reserved3; int /*<<< orphan*/  icb_disctime; int /*<<< orphan*/ * icb_enodemac; int /*<<< orphan*/ * icb_reserved2; int /*<<< orphan*/  icb_qos; int /*<<< orphan*/  icb_fwoptions3; int /*<<< orphan*/  icb_fwoptions2; int /*<<< orphan*/  icb_fwoptions1; int /*<<< orphan*/  icb_logintime; int /*<<< orphan*/  icb_idelaytimer; int /*<<< orphan*/ * icb_atioqaddr; int /*<<< orphan*/  icb_atioqlen; int /*<<< orphan*/  icb_atio_in; int /*<<< orphan*/ * icb_reserved1; int /*<<< orphan*/  icb_msixatio; int /*<<< orphan*/  icb_msixresp; int /*<<< orphan*/ * icb_priaddr; int /*<<< orphan*/ * icb_respaddr; int /*<<< orphan*/ * icb_rqstaddr; int /*<<< orphan*/  icb_prqstqlen; int /*<<< orphan*/  icb_ldn_nols; int /*<<< orphan*/  icb_rqstqlen; int /*<<< orphan*/  icb_rsltqlen; int /*<<< orphan*/  icb_priout; int /*<<< orphan*/  icb_retry_count; int /*<<< orphan*/  icb_rqstout; int /*<<< orphan*/  icb_rspnsin; int /*<<< orphan*/ * icb_nodename; int /*<<< orphan*/ * icb_portname; int /*<<< orphan*/  icb_hardaddr; int /*<<< orphan*/  icb_xchgcnt; int /*<<< orphan*/  icb_execthrottle; int /*<<< orphan*/  icb_maxfrmlen; int /*<<< orphan*/  icb_reserved0; int /*<<< orphan*/  icb_version; } ;
typedef  TYPE_1__ isp_icb_2400_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
isp_put_icb_2400(ispsoftc_t *isp, isp_icb_2400_t *src, isp_icb_2400_t *dst)
{
	int i;
	ISP_IOXPUT_16(isp, src->icb_version, &dst->icb_version);
	ISP_IOXPUT_16(isp, src->icb_reserved0, &dst->icb_reserved0);
	ISP_IOXPUT_16(isp, src->icb_maxfrmlen, &dst->icb_maxfrmlen);
	ISP_IOXPUT_16(isp, src->icb_execthrottle, &dst->icb_execthrottle);
	ISP_IOXPUT_16(isp, src->icb_xchgcnt, &dst->icb_xchgcnt);
	ISP_IOXPUT_16(isp, src->icb_hardaddr, &dst->icb_hardaddr);
	for (i = 0; i < 8; i++) {
		ISP_IOXPUT_8(isp, src->icb_portname[i], &dst->icb_portname[i]);
	}
	for (i = 0; i < 8; i++) {
		ISP_IOXPUT_8(isp, src->icb_nodename[i], &dst->icb_nodename[i]);
	}
	ISP_IOXPUT_16(isp, src->icb_rspnsin, &dst->icb_rspnsin);
	ISP_IOXPUT_16(isp, src->icb_rqstout, &dst->icb_rqstout);
	ISP_IOXPUT_16(isp, src->icb_retry_count, &dst->icb_retry_count);
	ISP_IOXPUT_16(isp, src->icb_priout, &dst->icb_priout);
	ISP_IOXPUT_16(isp, src->icb_rsltqlen, &dst->icb_rsltqlen);
	ISP_IOXPUT_16(isp, src->icb_rqstqlen, &dst->icb_rqstqlen);
	ISP_IOXPUT_16(isp, src->icb_ldn_nols, &dst->icb_ldn_nols);
	ISP_IOXPUT_16(isp, src->icb_prqstqlen, &dst->icb_prqstqlen);
	for (i = 0; i < 4; i++) {
		ISP_IOXPUT_16(isp, src->icb_rqstaddr[i], &dst->icb_rqstaddr[i]);
	}
	for (i = 0; i < 4; i++) {
		ISP_IOXPUT_16(isp, src->icb_respaddr[i], &dst->icb_respaddr[i]);
	}
	for (i = 0; i < 4; i++) {
		ISP_IOXPUT_16(isp, src->icb_priaddr[i], &dst->icb_priaddr[i]);
	}
	ISP_IOXPUT_16(isp, src->icb_msixresp, &dst->icb_msixresp);
	ISP_IOXPUT_16(isp, src->icb_msixatio, &dst->icb_msixatio);
	for (i = 0; i < 2; i++) {
		ISP_IOXPUT_16(isp, src->icb_reserved1[i], &dst->icb_reserved1[i]);
	}
	ISP_IOXPUT_16(isp, src->icb_atio_in, &dst->icb_atio_in);
	ISP_IOXPUT_16(isp, src->icb_atioqlen, &dst->icb_atioqlen);
	for (i = 0; i < 4; i++) {
		ISP_IOXPUT_16(isp, src->icb_atioqaddr[i], &dst->icb_atioqaddr[i]);
	}
	ISP_IOXPUT_16(isp, src->icb_idelaytimer, &dst->icb_idelaytimer);
	ISP_IOXPUT_16(isp, src->icb_logintime, &dst->icb_logintime);
	ISP_IOXPUT_32(isp, src->icb_fwoptions1, &dst->icb_fwoptions1);
	ISP_IOXPUT_32(isp, src->icb_fwoptions2, &dst->icb_fwoptions2);
	ISP_IOXPUT_32(isp, src->icb_fwoptions3, &dst->icb_fwoptions3);
	ISP_IOXPUT_16(isp, src->icb_qos, &dst->icb_qos);
	for (i = 0; i < 3; i++)
		ISP_IOXPUT_16(isp, src->icb_reserved2[i], &dst->icb_reserved2[i]);
	for (i = 0; i < 3; i++)
		ISP_IOXPUT_16(isp, src->icb_enodemac[i], &dst->icb_enodemac[i]);
	ISP_IOXPUT_16(isp, src->icb_disctime, &dst->icb_disctime);
	for (i = 0; i < 4; i++)
		ISP_IOXPUT_16(isp, src->icb_reserved3[i], &dst->icb_reserved3[i]);
}