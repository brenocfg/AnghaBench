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
typedef  size_t u32 ;
struct tp_mib_data {int dummy; } ;
struct cudbg_init {struct adapter* adap; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ addr; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 size_t TP_MIB_SIZE ; 
 int /*<<< orphan*/  t4_tp_mib_read (struct adapter*,int /*<<< orphan*/ *,int,size_t,int) ; 
 TYPE_1__* tp_mib ; 

__attribute__((used)) static u32 read_tp_mib_data(struct cudbg_init *pdbg_init,
			    struct tp_mib_data **ppTp_Mib)
{
	struct adapter *padap = pdbg_init->adap;
	u32 i = 0;

	for (i = 0; i < TP_MIB_SIZE; i++) {
		t4_tp_mib_read(padap, &tp_mib[i].value, 1,
				  (u32)tp_mib[i].addr, true);
	}
	*ppTp_Mib = (struct tp_mib_data *)&tp_mib[0];

	return 0;
}