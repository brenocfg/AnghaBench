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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct isp_sbussoftc {int* sbus_poff; } ;
typedef  int /*<<< orphan*/  ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BXR2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP_LOGDEBUG3 ; 
 int _BLK_REG_MASK ; 
 int _BLK_REG_SHFT ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
isp_sbus_rd_reg(ispsoftc_t *isp, int regoff)
{
	uint16_t rval;
	struct isp_sbussoftc *sbs = (struct isp_sbussoftc *) isp;
	int offset = sbs->sbus_poff[(regoff & _BLK_REG_MASK) >> _BLK_REG_SHFT];
	offset += (regoff & 0xff);
	rval = BXR2(isp, offset);
	isp_prt(isp, ISP_LOGDEBUG3,
	    "isp_sbus_rd_reg(off %x) = %x", regoff, rval);
	return (rval);
}