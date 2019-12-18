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
typedef  void* uint64_t ;
struct debug_reg {int /*<<< orphan*/  dbcr0; void* dac2; void* dac1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBCR0_DAC1R ; 
 int /*<<< orphan*/  DBCR0_DAC1W ; 
 int /*<<< orphan*/  DBCR0_DAC2R ; 
 int /*<<< orphan*/  DBCR0_DAC2W ; 
 int /*<<< orphan*/  DBCR0_IDM ; 
 int EINVAL ; 
 int KVMPPC_DEBUG_WATCH_READ ; 
 int KVMPPC_DEBUG_WATCH_WRITE ; 

__attribute__((used)) static int kvmppc_booke_add_watchpoint(struct debug_reg *dbg_reg, uint64_t addr,
				       int type, int index)
{
	switch (index) {
	case 0:
		if (type & KVMPPC_DEBUG_WATCH_READ)
			dbg_reg->dbcr0 |= DBCR0_DAC1R;
		if (type & KVMPPC_DEBUG_WATCH_WRITE)
			dbg_reg->dbcr0 |= DBCR0_DAC1W;
		dbg_reg->dac1 = addr;
		break;
	case 1:
		if (type & KVMPPC_DEBUG_WATCH_READ)
			dbg_reg->dbcr0 |= DBCR0_DAC2R;
		if (type & KVMPPC_DEBUG_WATCH_WRITE)
			dbg_reg->dbcr0 |= DBCR0_DAC2W;
		dbg_reg->dac2 = addr;
		break;
	default:
		return -EINVAL;
	}

	dbg_reg->dbcr0 |= DBCR0_IDM;
	return 0;
}