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
struct TYPE_4__ {int /*<<< orphan*/  parameter; int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  seq_cnt; int /*<<< orphan*/  df_ctl; int /*<<< orphan*/  seq_id; int /*<<< orphan*/ * f_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/ * s_id; int /*<<< orphan*/  cs_ctl; int /*<<< orphan*/ * d_id; int /*<<< orphan*/  r_ctl; } ;
typedef  TYPE_1__ fc_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOZGET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOZGET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOZGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
isp_get_fc_hdr(ispsoftc_t *isp, fc_hdr_t *src, fc_hdr_t *dst)
{
        ISP_IOZGET_8(isp, &src->r_ctl, dst->r_ctl);
        ISP_IOZGET_8(isp, &src->d_id[0], dst->d_id[0]);
        ISP_IOZGET_8(isp, &src->d_id[1], dst->d_id[1]);
        ISP_IOZGET_8(isp, &src->d_id[2], dst->d_id[2]);
        ISP_IOZGET_8(isp, &src->cs_ctl, dst->cs_ctl);
        ISP_IOZGET_8(isp, &src->s_id[0], dst->s_id[0]);
        ISP_IOZGET_8(isp, &src->s_id[1], dst->s_id[1]);
        ISP_IOZGET_8(isp, &src->s_id[2], dst->s_id[2]);
        ISP_IOZGET_8(isp, &src->type, dst->type);
        ISP_IOZGET_8(isp, &src->f_ctl[0], dst->f_ctl[0]);
        ISP_IOZGET_8(isp, &src->f_ctl[1], dst->f_ctl[1]);
        ISP_IOZGET_8(isp, &src->f_ctl[2], dst->f_ctl[2]);
        ISP_IOZGET_8(isp, &src->seq_id, dst->seq_id);
        ISP_IOZGET_8(isp, &src->df_ctl, dst->df_ctl);
        ISP_IOZGET_16(isp, &src->seq_cnt, dst->seq_cnt);
        ISP_IOZGET_16(isp, &src->ox_id, dst->ox_id);
        ISP_IOZGET_16(isp, &src->rx_id, dst->rx_id);
        ISP_IOZGET_32(isp, &src->parameter, dst->parameter);
}