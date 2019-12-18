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
struct TYPE_4__ {int /*<<< orphan*/ * abrt_reserved1; int /*<<< orphan*/  abrt_vpidx; int /*<<< orphan*/  abrt_tidhi; int /*<<< orphan*/  abrt_tidlo; int /*<<< orphan*/ * abrt_reserved; int /*<<< orphan*/  abrt_queue_number; int /*<<< orphan*/  abrt_cmd_handle; int /*<<< orphan*/  abrt_options; int /*<<< orphan*/  abrt_nphdl; int /*<<< orphan*/  abrt_handle; int /*<<< orphan*/  abrt_header; } ;
typedef  TYPE_1__ isp24xx_abrt_t ;

/* Variables and functions */
 int ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_put_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_24xx_abrt(ispsoftc_t *isp, isp24xx_abrt_t *src, isp24xx_abrt_t *dst)
{
	int i;
	isp_put_hdr(isp, &src->abrt_header, &dst->abrt_header);
	ISP_IOXPUT_32(isp, src->abrt_handle, &dst->abrt_handle);
	ISP_IOXPUT_16(isp, src->abrt_nphdl, &dst->abrt_nphdl);
	ISP_IOXPUT_16(isp, src->abrt_options, &dst->abrt_options);
	ISP_IOXPUT_32(isp, src->abrt_cmd_handle, &dst->abrt_cmd_handle);
	ISP_IOXPUT_16(isp, src->abrt_queue_number, &dst->abrt_queue_number);
	for (i = 0; i < ASIZE(src->abrt_reserved); i++) {
		ISP_IOXPUT_8(isp, src->abrt_reserved[i], &dst->abrt_reserved[i]);
	}
	ISP_IOXPUT_16(isp, src->abrt_tidlo, &dst->abrt_tidlo);
	ISP_IOXPUT_8(isp, src->abrt_tidhi, &dst->abrt_tidhi);
	ISP_IOXPUT_8(isp, src->abrt_vpidx, &dst->abrt_vpidx);
	for (i = 0; i < ASIZE(src->abrt_reserved1); i++) {
		ISP_IOXPUT_8(isp, src->abrt_reserved1[i], &dst->abrt_reserved1[i]);
	}
}