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
struct TYPE_2__ {scalar_t__ se_err; } ;
union efl_core_int {TYPE_1__ s; void* value; } ;
typedef  void* u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 void* EFL_CORE_INTX (int) ; 
 void* EFL_CORE_SE_ERR_INTX (int) ; 
 int NR_CLUSTERS ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int,void*) ; 
 void* nitrox_read_csr (struct nitrox_device*,void*) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,void*,void*) ; 

__attribute__((used)) static void clear_efl_err_intr(struct nitrox_device *ndev)
{
	int i;

	for (i = 0; i < NR_CLUSTERS; i++) {
		union efl_core_int core_int;
		u64 value, offset;

		offset = EFL_CORE_INTX(i);
		core_int.value = nitrox_read_csr(ndev, offset);
		nitrox_write_csr(ndev, offset, core_int.value);
		dev_err_ratelimited(DEV(ndev), "ELF_CORE(%d)_INT  0x%016llx\n",
				    i, core_int.value);
		if (core_int.s.se_err) {
			offset = EFL_CORE_SE_ERR_INTX(i);
			value = nitrox_read_csr(ndev, offset);
			nitrox_write_csr(ndev, offset, value);
		}
	}
}