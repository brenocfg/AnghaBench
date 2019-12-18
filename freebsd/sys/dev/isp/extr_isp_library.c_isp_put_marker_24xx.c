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
struct TYPE_4__ {int /*<<< orphan*/ * mrk_reserved3; int /*<<< orphan*/ * mrk_lun; int /*<<< orphan*/  mrk_reserved2; int /*<<< orphan*/  mrk_vphdl; int /*<<< orphan*/  mrk_reserved1; int /*<<< orphan*/  mrk_reserved0; int /*<<< orphan*/  mrk_modifier; int /*<<< orphan*/  mrk_nphdl; int /*<<< orphan*/  mrk_handle; int /*<<< orphan*/  mrk_header; } ;
typedef  TYPE_1__ isp_marker_24xx_t ;

/* Variables and functions */
 int ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_IOXPUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp_put_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_put_marker_24xx(ispsoftc_t *isp, isp_marker_24xx_t *src, isp_marker_24xx_t *dst)
{
	int i;
	isp_put_hdr(isp, &src->mrk_header, &dst->mrk_header);
	ISP_IOXPUT_32(isp, src->mrk_handle, &dst->mrk_handle);
	ISP_IOXPUT_16(isp, src->mrk_nphdl, &dst->mrk_nphdl);
	ISP_IOXPUT_8(isp, src->mrk_modifier, &dst->mrk_modifier);
	ISP_IOXPUT_8(isp, src->mrk_reserved0, &dst->mrk_reserved0);
	ISP_IOXPUT_8(isp, src->mrk_reserved1, &dst->mrk_reserved1);
	ISP_IOXPUT_8(isp, src->mrk_vphdl, &dst->mrk_vphdl);
	ISP_IOXPUT_8(isp, src->mrk_reserved2, &dst->mrk_reserved2);
	for (i = 0; i < ASIZE(src->mrk_lun); i++) {
		ISP_IOXPUT_8(isp, src->mrk_lun[i], &dst->mrk_lun[i]);
	}
	for (i = 0; i < ASIZE(src->mrk_reserved3); i++) {
		ISP_IOXPUT_8(isp, src->mrk_reserved3[i], &dst->mrk_reserved3[i]);
	}
}