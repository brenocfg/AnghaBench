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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_CMM_TCB_BASE ; 
 int TCB_SIZE ; 
 int /*<<< orphan*/  be32toh (int) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 int /*<<< orphan*/  read_via_memwin (struct adapter*,int /*<<< orphan*/ ,int,int*,int) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t
get_filter_hits(struct adapter *sc, uint32_t tid)
{
	uint32_t tcb_addr;

	tcb_addr = t4_read_reg(sc, A_TP_CMM_TCB_BASE) + tid * TCB_SIZE;

	if (is_t4(sc)) {
		uint64_t hits;

		read_via_memwin(sc, 0, tcb_addr + 16, (uint32_t *)&hits, 8);
		return (be64toh(hits));
	} else {
		uint32_t hits;

		read_via_memwin(sc, 0, tcb_addr + 24, &hits, 4);
		return (be32toh(hits));
	}
}