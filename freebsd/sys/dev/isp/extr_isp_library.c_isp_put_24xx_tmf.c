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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_4__ {int /*<<< orphan*/ * tmf_reserved2; int /*<<< orphan*/  tmf_vpidx; int /*<<< orphan*/  tmf_tidhi; int /*<<< orphan*/  tmf_tidlo; int /*<<< orphan*/ * tmf_reserved1; int /*<<< orphan*/  tmf_flags; int /*<<< orphan*/ * tmf_lun; int /*<<< orphan*/ * tmf_reserved0; int /*<<< orphan*/  tmf_timeout; int /*<<< orphan*/  tmf_delay; int /*<<< orphan*/  tmf_nphdl; int /*<<< orphan*/  tmf_handle; int /*<<< orphan*/  tmf_header; } ;
typedef  TYPE_1__ isp24xx_tmf_t ;

/* Variables and functions */
 int ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_SWAP32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_put_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_24xx_tmf(ispsoftc_t *isp, isp24xx_tmf_t *src, isp24xx_tmf_t *dst)
{
	int i;
	uint32_t *a, *b;

	isp_put_hdr(isp, &src->tmf_header, &dst->tmf_header);
	ISP_IOXPUT_32(isp, src->tmf_handle, &dst->tmf_handle);
	ISP_IOXPUT_16(isp, src->tmf_nphdl, &dst->tmf_nphdl);
	ISP_IOXPUT_16(isp, src->tmf_delay, &dst->tmf_delay);
	ISP_IOXPUT_16(isp, src->tmf_timeout, &dst->tmf_timeout);
	for (i = 0; i < ASIZE(src->tmf_reserved0); i++) {
		ISP_IOXPUT_8(isp, src->tmf_reserved0[i], &dst->tmf_reserved0[i]);
	}
	a = (uint32_t *) src->tmf_lun;
	b = (uint32_t *) dst->tmf_lun;
	for (i = 0; i < (ASIZE(src->tmf_lun) >> 2); i++ ) {
		*b++ = ISP_SWAP32(isp, *a++);
	}
	ISP_IOXPUT_32(isp, src->tmf_flags, &dst->tmf_flags);
	for (i = 0; i < ASIZE(src->tmf_reserved1); i++) {
		ISP_IOXPUT_8(isp, src->tmf_reserved1[i], &dst->tmf_reserved1[i]);
	}
	ISP_IOXPUT_16(isp, src->tmf_tidlo, &dst->tmf_tidlo);
	ISP_IOXPUT_8(isp, src->tmf_tidhi, &dst->tmf_tidhi);
	ISP_IOXPUT_8(isp, src->tmf_vpidx, &dst->tmf_vpidx);
	for (i = 0; i < ASIZE(src->tmf_reserved2); i++) {
		ISP_IOXPUT_8(isp, src->tmf_reserved2[i], &dst->tmf_reserved2[i]);
	}
}