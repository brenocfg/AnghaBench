#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mii_bus {int dummy; } ;
struct TYPE_7__ {int dat; scalar_t__ val; } ;
struct TYPE_8__ {TYPE_2__ s; } ;
typedef  TYPE_3__ cvmx_smix_rd_dat_t ;
struct TYPE_6__ {int phy_adr; int reg_adr; int /*<<< orphan*/  phy_op; } ;
struct TYPE_9__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_4__ cvmx_smix_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CVMX_SMIX_CMD (int) ; 
 int /*<<< orphan*/  MDIO_CLAUSE_22_READ ; 
 int /*<<< orphan*/  OCTEON_FEATURE_MDIO_CLAUSE_45 ; 
 TYPE_3__ __cvmx_mdio_read_rd_dat (int) ; 
 int /*<<< orphan*/  __cvmx_mdio_set_clause22_mode (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 
 int mdiobus_read (struct mii_bus*,int,int) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 
 struct mii_bus** octeon_mdiobuses ; 

__attribute__((used)) static inline int cvmx_mdio_read(int bus_id, int phy_id, int location)
{
#if defined(CVMX_BUILD_FOR_LINUX_KERNEL) && defined(CONFIG_PHYLIB)
	struct mii_bus *bus;
	int rv;

	BUG_ON(bus_id > 3 || bus_id < 0);

	bus = octeon_mdiobuses[bus_id];
	if (bus == NULL)
		return -1;

	rv = mdiobus_read(bus, phy_id, location);

	if (rv < 0)
		return -1;
	return rv;
#else
    cvmx_smix_cmd_t smi_cmd;
    cvmx_smix_rd_dat_t smi_rd;

    if (octeon_has_feature(OCTEON_FEATURE_MDIO_CLAUSE_45))
        __cvmx_mdio_set_clause22_mode(bus_id);

    smi_cmd.u64 = 0;
    smi_cmd.s.phy_op = MDIO_CLAUSE_22_READ;
    smi_cmd.s.phy_adr = phy_id;
    smi_cmd.s.reg_adr = location;
    cvmx_write_csr(CVMX_SMIX_CMD(bus_id), smi_cmd.u64);

    smi_rd = __cvmx_mdio_read_rd_dat(bus_id);
    if (smi_rd.s.val)
        return smi_rd.s.dat;
    else
        return -1;
#endif
}