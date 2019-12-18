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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_CYCLE ; 
 int /*<<< orphan*/  CSR_INSTRET ; 
 int /*<<< orphan*/  EINVAL ; 
 int RISCV_MAX_COUNTERS ; 
#define  RISCV_PMU_CYCLE 129 
#define  RISCV_PMU_INSTRET 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  csr_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 read_counter(int idx)
{
	u64 val = 0;

	switch (idx) {
	case RISCV_PMU_CYCLE:
		val = csr_read(CSR_CYCLE);
		break;
	case RISCV_PMU_INSTRET:
		val = csr_read(CSR_INSTRET);
		break;
	default:
		WARN_ON_ONCE(idx < 0 ||	idx > RISCV_MAX_COUNTERS);
		return -EINVAL;
	}

	return val;
}