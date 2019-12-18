#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ base; scalar_t__ width; } ;
struct TYPE_5__ {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ cvmx_mio_boot_reg_cfgx_t ;
struct TYPE_6__ {scalar_t__ board_type; scalar_t__ compact_flash_common_base_addr; scalar_t__ compact_flash_attribute_base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
#define  CF_16 130 
#define  CF_8 129 
#define  CF_TRUE_IDE_8 128 
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int /*<<< orphan*/  CVMX_MIO_BOOT_REG_CFGX (int) ; 
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_TRIES ; 
 int STATUS_BSY ; 
 int /*<<< orphan*/  TF_STATUS ; 
 int /*<<< orphan*/  WAIT_DELAY ; 
 int /*<<< orphan*/  base_addr ; 
 size_t bus_type ; 
 int cf_inb_16 (int /*<<< orphan*/ ) ; 
 int cf_inb_8 (int /*<<< orphan*/ ) ; 
 char** cf_type ; 
 int /*<<< orphan*/  cvmx_phys_to_ptr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 TYPE_3__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void cf_identify (driver_t *drv, device_t parent)
{
	int bus_region;
	int count = 0;
	cvmx_mio_boot_reg_cfgx_t cfg;
	uint64_t phys_base;
	
    	if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM)
		return;

	phys_base = cvmx_sysinfo_get()->compact_flash_common_base_addr;
	if (phys_base == 0)
		return;
	base_addr = cvmx_phys_to_ptr(phys_base);

        for (bus_region = 0; bus_region < 8; bus_region++)
        {
                cfg.u64 = cvmx_read_csr(CVMX_MIO_BOOT_REG_CFGX(bus_region));
                if (cfg.s.base == phys_base >> 16)
                {
			if (cvmx_sysinfo_get()->compact_flash_attribute_base_addr == 0)
				bus_type = CF_TRUE_IDE_8;
			else
				bus_type = (cfg.s.width) ? CF_16 : CF_8;
                        printf("Compact flash found in bootbus region %d (%s).\n", bus_region, cf_type[bus_type]);
                        break;
                }
        }

	switch (bus_type)
	{
	case CF_8:
	case CF_TRUE_IDE_8:
		/* Check if CF is inserted */
		while (cf_inb_8(TF_STATUS) & STATUS_BSY) {
			if ((count++) == NR_TRIES ) {
				printf("Compact Flash not present\n");
				return;
                	}
			DELAY(WAIT_DELAY);
        	}
		break;
	case CF_16:
	default:
		/* Check if CF is inserted */
		while (cf_inb_16(TF_STATUS) & STATUS_BSY) {
			if ((count++) == NR_TRIES ) {
				printf("Compact Flash not present\n");
				return;
                	}
			DELAY(WAIT_DELAY);
        	}
		break;
	}

	BUS_ADD_CHILD(parent, 0, "cf", 0);
}