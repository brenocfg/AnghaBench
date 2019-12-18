#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct isp_sbussoftc {int* sbus_poff; } ;
struct TYPE_5__ {int /*<<< orphan*/  isp_regs; } ;
typedef  TYPE_1__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_LOGDEBUG3 ; 
 int /*<<< orphan*/  MEMORYBARRIER (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SYNC_REG ; 
 int _BLK_REG_MASK ; 
 int _BLK_REG_SHFT ; 
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_prt (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isp_sbus_wr_reg(ispsoftc_t *isp, int regoff, uint32_t val)
{
	struct isp_sbussoftc *sbs = (struct isp_sbussoftc *) isp;
	int offset = sbs->sbus_poff[(regoff & _BLK_REG_MASK) >> _BLK_REG_SHFT];
	offset += (regoff & 0xff);
	isp_prt(isp, ISP_LOGDEBUG3,
	    "isp_sbus_wr_reg(off %x) = %x", regoff, val);
	bus_write_2(isp->isp_regs, offset, val);
	MEMORYBARRIER(isp, SYNC_REG, offset, 2, -1);
}