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
typedef  int uint32_t ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MA_EDRAM0_BAR ; 
 int /*<<< orphan*/  A_MA_EDRAM1_BAR ; 
 int /*<<< orphan*/  A_MA_EXT_MEMORY1_BAR ; 
 int /*<<< orphan*/  A_MA_EXT_MEMORY_BAR ; 
 int /*<<< orphan*/  A_MA_TARGET_MEM_ENABLE ; 
 int EINVAL ; 
 int F_EDRAM0_ENABLE ; 
 int F_EDRAM1_ENABLE ; 
 int F_EXT_MEM1_ENABLE ; 
 int F_EXT_MEM_ENABLE ; 
 int G_EDRAM0_BASE (int) ; 
 int G_EDRAM1_BASE (int) ; 
 int G_EXT_MEM1_BASE (int) ; 
 int G_EXT_MEM_BASE (int) ; 
#define  MEM_EDC0 131 
#define  MEM_EDC1 130 
#define  MEM_MC 129 
#define  MEM_MC1 128 
 int fwmtype_to_hwmtype (int) ; 
 int /*<<< orphan*/  is_t5 (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int validate_mem_range (struct adapter*,int,int) ; 

__attribute__((used)) static int
validate_mt_off_len(struct adapter *sc, int mtype, uint32_t off, uint32_t len,
    uint32_t *addr)
{
	uint32_t em, addr_len, maddr;

	/* Memory can only be accessed in naturally aligned 4 byte units */
	if (off & 3 || len & 3 || len == 0)
		return (EINVAL);

	em = t4_read_reg(sc, A_MA_TARGET_MEM_ENABLE);
	switch (fwmtype_to_hwmtype(mtype)) {
	case MEM_EDC0:
		if (!(em & F_EDRAM0_ENABLE))
			return (EINVAL);
		addr_len = t4_read_reg(sc, A_MA_EDRAM0_BAR);
		maddr = G_EDRAM0_BASE(addr_len) << 20;
		break;
	case MEM_EDC1:
		if (!(em & F_EDRAM1_ENABLE))
			return (EINVAL);
		addr_len = t4_read_reg(sc, A_MA_EDRAM1_BAR);
		maddr = G_EDRAM1_BASE(addr_len) << 20;
		break;
	case MEM_MC:
		if (!(em & F_EXT_MEM_ENABLE))
			return (EINVAL);
		addr_len = t4_read_reg(sc, A_MA_EXT_MEMORY_BAR);
		maddr = G_EXT_MEM_BASE(addr_len) << 20;
		break;
	case MEM_MC1:
		if (!is_t5(sc) || !(em & F_EXT_MEM1_ENABLE))
			return (EINVAL);
		addr_len = t4_read_reg(sc, A_MA_EXT_MEMORY1_BAR);
		maddr = G_EXT_MEM1_BASE(addr_len) << 20;
		break;
	default:
		return (EINVAL);
	}

	*addr = maddr + off;	/* global address */
	return (validate_mem_range(sc, *addr, len));
}