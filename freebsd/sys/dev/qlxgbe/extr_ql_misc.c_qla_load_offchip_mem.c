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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;
struct TYPE_4__ {int /*<<< orphan*/  data_lo; int /*<<< orphan*/  data_hi; int /*<<< orphan*/  data_ulo; int /*<<< orphan*/  data_uhi; } ;
typedef  TYPE_1__ q80_offchip_mem_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int ql_rdwr_offchip_mem (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla_load_offchip_mem(qla_host_t *ha, uint64_t addr, uint32_t *data32,
        uint32_t len32)
{
        q80_offchip_mem_val_t val;
        int             ret = 0;

        while (len32) {
                if (len32 > 4) {
                        val.data_lo = *data32++;
                        val.data_hi = *data32++;
                        val.data_ulo = *data32++;
                        val.data_uhi = *data32++;
                        len32 -= 4;
                        if (ql_rdwr_offchip_mem(ha, addr, &val, 0))
                                return -1;

                        addr += (uint64_t)16;
                } else {
                        break;
                }
        }

        bzero(&val, sizeof(q80_offchip_mem_val_t));

        switch (len32) {
        case 3:
                val.data_lo = *data32++;
                val.data_hi = *data32++;
                val.data_ulo = *data32++;
                 ret = ql_rdwr_offchip_mem(ha, addr, &val, 0);
                break;

        case 2:
                val.data_lo = *data32++;
                val.data_hi = *data32++;
                 ret = ql_rdwr_offchip_mem(ha, addr, &val, 0);
                break;

        case 1:
                val.data_lo = *data32++;
                ret = ql_rdwr_offchip_mem(ha, addr, &val, 0);
                break;

        default:
                break;

        }
        return ret;
}