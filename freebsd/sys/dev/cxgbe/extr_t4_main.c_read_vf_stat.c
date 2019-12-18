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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int u32 ;
struct adapter {int flags; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_INDIR_CMD ; 
 int /*<<< orphan*/  A_PL_INDIR_DATA ; 
 int IS_VF ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  VF_MPS_REG (int) ; 
 int V_PL_ADDR (int /*<<< orphan*/ ) ; 
 int V_PL_AUTOINC (int) ; 
 int V_PL_VFID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint64_t
read_vf_stat(struct adapter *sc, u_int vin, int reg)
{
	u32 stats[2];

	mtx_assert(&sc->reg_lock, MA_OWNED);
	if (sc->flags & IS_VF) {
		stats[0] = t4_read_reg(sc, VF_MPS_REG(reg));
		stats[1] = t4_read_reg(sc, VF_MPS_REG(reg + 4));
	} else {
		t4_write_reg(sc, A_PL_INDIR_CMD, V_PL_AUTOINC(1) |
		    V_PL_VFID(vin) | V_PL_ADDR(VF_MPS_REG(reg)));
		stats[0] = t4_read_reg(sc, A_PL_INDIR_DATA);
		stats[1] = t4_read_reg(sc, A_PL_INDIR_DATA);
	}
	return (((uint64_t)stats[1]) << 32 | stats[0]);
}