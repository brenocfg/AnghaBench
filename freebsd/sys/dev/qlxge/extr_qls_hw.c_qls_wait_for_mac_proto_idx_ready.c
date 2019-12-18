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
typedef  int uint32_t ;
struct TYPE_4__ {int qla_initiate_recovery; } ;
typedef  TYPE_1__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q81_CTL_MAC_PROTO_ADDR_INDEX ; 
 int /*<<< orphan*/  QLA_USEC_DELAY (int) ; 
 int READ_REG32 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qls_wait_for_mac_proto_idx_ready(qla_host_t *ha, uint32_t op)
{
	uint32_t data32;
	uint32_t count = 3;

	while (count--) {
		data32 = READ_REG32(ha, Q81_CTL_MAC_PROTO_ADDR_INDEX);

		if (data32 & op)
			return (0);

		QLA_USEC_DELAY(100);
	}
	ha->qla_initiate_recovery = 1;
	return (-1);
}