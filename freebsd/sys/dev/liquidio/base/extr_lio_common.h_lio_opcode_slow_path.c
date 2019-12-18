#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  subcode; int /*<<< orphan*/  opcode; } ;
union octeon_rh {TYPE_1__ r; } ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_OPCODE_NIC ; 
 int /*<<< orphan*/  LIO_OPCODE_NIC_NW_DATA ; 
 scalar_t__ LIO_OPCODE_SUBCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
lio_opcode_slow_path(union octeon_rh *rh)
{
	uint16_t	subcode1, subcode2;

	subcode1 = LIO_OPCODE_SUBCODE((rh)->r.opcode, (rh)->r.subcode);
	subcode2 = LIO_OPCODE_SUBCODE(LIO_OPCODE_NIC, LIO_OPCODE_NIC_NW_DATA);

	return (subcode2 != subcode1);
}