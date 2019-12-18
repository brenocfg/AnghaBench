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
struct hwrm_func_drv_rgtr_input {int ver_maj; int ver_min; int ver_upd; int /*<<< orphan*/  os_type; int /*<<< orphan*/  enables; int /*<<< orphan*/  member_0; } ;
struct bnxt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_FUNC_DRV_RGTR ; 
 int HWRM_FUNC_DRV_RGTR_INPUT_ENABLES_OS_TYPE ; 
 int HWRM_FUNC_DRV_RGTR_INPUT_ENABLES_VER ; 
 int /*<<< orphan*/  HWRM_FUNC_DRV_RGTR_INPUT_OS_TYPE_FREEBSD ; 
 int __FreeBSD_version ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_func_drv_rgtr_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int hwrm_send_message (struct bnxt_softc*,struct hwrm_func_drv_rgtr_input*,int) ; 

int
bnxt_hwrm_func_drv_rgtr(struct bnxt_softc *softc)
{
	struct hwrm_func_drv_rgtr_input req = {0};

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_FUNC_DRV_RGTR);

	req.enables = htole32(HWRM_FUNC_DRV_RGTR_INPUT_ENABLES_VER |
	    HWRM_FUNC_DRV_RGTR_INPUT_ENABLES_OS_TYPE);
	req.os_type = htole16(HWRM_FUNC_DRV_RGTR_INPUT_OS_TYPE_FREEBSD);

	req.ver_maj = __FreeBSD_version / 100000;
	req.ver_min = (__FreeBSD_version / 1000) % 100;
	req.ver_upd = (__FreeBSD_version / 100) % 10;

	return hwrm_send_message(softc, &req, sizeof(req));
}