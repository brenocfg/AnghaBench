#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
struct thread {int dummy; } ;
struct dump_header {int dummy; } ;
struct cdev {scalar_t__ si_drv1; } ;
struct TYPE_10__ {char* bc_ver_str; int /*<<< orphan*/  flash_size; } ;
struct bxe_softc {int pcie_func; char* fw_ver_str; int pcie_bus; int pcie_device; char* mac_addr_str; int /*<<< orphan*/  dev; int /*<<< orphan*/  grcdump_done; int /*<<< orphan*/  grcdump_started; int /*<<< orphan*/ * grc_dump; TYPE_1__ devinfo; int /*<<< orphan*/  trigger_grcdump; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_11__ {int /*<<< orphan*/  reg_val; int /*<<< orphan*/  reg_id; int /*<<< orphan*/  reg_access_type; int /*<<< orphan*/  reg_cmd; } ;
typedef  TYPE_2__ bxe_reg_rdw_t ;
struct TYPE_12__ {int /*<<< orphan*/  mac_addr_str; } ;
typedef  TYPE_3__ bxe_perm_mac_addr_t ;
struct TYPE_13__ {int /*<<< orphan*/  cfg_width; int /*<<< orphan*/  cfg_val; int /*<<< orphan*/  cfg_id; int /*<<< orphan*/  cfg_cmd; } ;
typedef  TYPE_4__ bxe_pcicfg_rdw_t ;
struct TYPE_14__ {int pci_func; int grcdump_size; int grcdump_dwords; int /*<<< orphan*/ * grcdump; } ;
typedef  TYPE_5__ bxe_grcdump_t ;
struct TYPE_15__ {int reg_buf_len; int /*<<< orphan*/ * reg_buf; } ;
typedef  TYPE_6__ bxe_get_regs_t ;
typedef  int /*<<< orphan*/  bxe_eeprom_t ;
struct TYPE_16__ {int reg_dump_len; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  eeprom_dump_len; int /*<<< orphan*/  stormfw_version; int /*<<< orphan*/  mfw_version; int /*<<< orphan*/  drv_version; int /*<<< orphan*/  drv_name; } ;
typedef  TYPE_7__ bxe_drvinfo_t ;
struct TYPE_17__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
typedef  TYPE_8__ bxe_dev_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGW (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_BUS_INFO_LENGTH ; 
#define  BXE_DEV_SETTING 136 
 char* BXE_DRIVER_VERSION ; 
#define  BXE_DRV_INFO 135 
 int BXE_DRV_NAME_LENGTH ; 
 int BXE_DRV_VERSION_LENGTH ; 
#define  BXE_EEPROM 134 
#define  BXE_GET_REGS 133 
#define  BXE_GRC_DUMP 132 
#define  BXE_GRC_DUMP_SIZE 131 
#define  BXE_MAC_ADDR 130 
 int BXE_MFW_VERSION_LENGTH ; 
#define  BXE_RDW_PCICFG 129 
#define  BXE_RDW_REG 128 
 int /*<<< orphan*/  BXE_READ_PCICFG ; 
 int /*<<< orphan*/  BXE_READ_REG_CMD ; 
 int /*<<< orphan*/  BXE_REG_ACCESS_DIRECT ; 
 int BXE_STORMFW_VERSION_LENGTH ; 
 int /*<<< orphan*/  BXE_WRITE_PCICFG ; 
 int /*<<< orphan*/  BXE_WRITE_REG_CMD ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bxe_eeprom_rd_wr (struct bxe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxe_get_settings (struct bxe_softc*,TYPE_8__*) ; 
 int bxe_get_total_regs_len32 (struct bxe_softc*) ; 
 int bxe_grc_dump (struct bxe_softc*) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static int
bxe_eioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
        struct thread *td)
{
    struct bxe_softc    *sc;
    int                 rval = 0;
    device_t            pci_dev;
    bxe_grcdump_t       *dump = NULL;
    int grc_dump_size;
    bxe_drvinfo_t   *drv_infop = NULL;
    bxe_dev_setting_t  *dev_p;
    bxe_dev_setting_t  dev_set;
    bxe_get_regs_t  *reg_p;
    bxe_reg_rdw_t *reg_rdw_p;
    bxe_pcicfg_rdw_t *cfg_rdw_p;
    bxe_perm_mac_addr_t *mac_addr_p;


    if ((sc = (struct bxe_softc *)dev->si_drv1) == NULL)
        return ENXIO;

    pci_dev= sc->dev;

    dump = (bxe_grcdump_t *)data;

    switch(cmd) {

        case BXE_GRC_DUMP_SIZE:
            dump->pci_func = sc->pcie_func;
            dump->grcdump_size =
                (bxe_get_total_regs_len32(sc) * sizeof(uint32_t)) +
                     sizeof(struct  dump_header);
            break;

        case BXE_GRC_DUMP:
            
            grc_dump_size = (bxe_get_total_regs_len32(sc) * sizeof(uint32_t)) +
                                sizeof(struct  dump_header);
            if ((!sc->trigger_grcdump) || (dump->grcdump == NULL) ||
                (dump->grcdump_size < grc_dump_size)) {
                rval = EINVAL;
                break;
            }

            if((sc->trigger_grcdump) && (!sc->grcdump_done) &&
                (!sc->grcdump_started)) {
                rval =  bxe_grc_dump(sc);
            }

            if((!rval) && (sc->grcdump_done) && (sc->grcdump_started) &&
                (sc->grc_dump != NULL))  {
                dump->grcdump_dwords = grc_dump_size >> 2;
                rval = copyout(sc->grc_dump, dump->grcdump, grc_dump_size);
                free(sc->grc_dump, M_DEVBUF);
                sc->grc_dump = NULL;
                sc->grcdump_started = 0;
                sc->grcdump_done = 0;
            }

            break;

        case BXE_DRV_INFO:
            drv_infop = (bxe_drvinfo_t *)data;
            snprintf(drv_infop->drv_name, BXE_DRV_NAME_LENGTH, "%s", "bxe");
            snprintf(drv_infop->drv_version, BXE_DRV_VERSION_LENGTH, "v:%s",
                BXE_DRIVER_VERSION);
            snprintf(drv_infop->mfw_version, BXE_MFW_VERSION_LENGTH, "%s",
                sc->devinfo.bc_ver_str);
            snprintf(drv_infop->stormfw_version, BXE_STORMFW_VERSION_LENGTH,
                "%s", sc->fw_ver_str);
            drv_infop->eeprom_dump_len = sc->devinfo.flash_size;
            drv_infop->reg_dump_len =
                (bxe_get_total_regs_len32(sc) * sizeof(uint32_t))
                    + sizeof(struct  dump_header);
            snprintf(drv_infop->bus_info, BXE_BUS_INFO_LENGTH, "%d:%d:%d",
                sc->pcie_bus, sc->pcie_device, sc->pcie_func);
            break;

        case BXE_DEV_SETTING:
            dev_p = (bxe_dev_setting_t *)data;
            bxe_get_settings(sc, &dev_set);
            dev_p->supported = dev_set.supported;
            dev_p->advertising = dev_set.advertising;
            dev_p->speed = dev_set.speed;
            dev_p->duplex = dev_set.duplex;
            dev_p->port = dev_set.port;
            dev_p->phy_address = dev_set.phy_address;
            dev_p->autoneg = dev_set.autoneg;

            break;

        case BXE_GET_REGS:

            reg_p = (bxe_get_regs_t *)data;
            grc_dump_size = reg_p->reg_buf_len;

            if((!sc->grcdump_done) && (!sc->grcdump_started)) {
                bxe_grc_dump(sc);
            }
            if((sc->grcdump_done) && (sc->grcdump_started) &&
                (sc->grc_dump != NULL))  {
                rval = copyout(sc->grc_dump, reg_p->reg_buf, grc_dump_size);
                free(sc->grc_dump, M_DEVBUF);
                sc->grc_dump = NULL;
                sc->grcdump_started = 0;
                sc->grcdump_done = 0;
            }

            break;

        case BXE_RDW_REG:
            reg_rdw_p = (bxe_reg_rdw_t *)data;
            if((reg_rdw_p->reg_cmd == BXE_READ_REG_CMD) &&
                (reg_rdw_p->reg_access_type == BXE_REG_ACCESS_DIRECT))
                reg_rdw_p->reg_val = REG_RD(sc, reg_rdw_p->reg_id);

            if((reg_rdw_p->reg_cmd == BXE_WRITE_REG_CMD) &&
                (reg_rdw_p->reg_access_type == BXE_REG_ACCESS_DIRECT))
                REG_WR(sc, reg_rdw_p->reg_id, reg_rdw_p->reg_val);

            break;

        case BXE_RDW_PCICFG:
            cfg_rdw_p = (bxe_pcicfg_rdw_t *)data;
            if(cfg_rdw_p->cfg_cmd == BXE_READ_PCICFG) {

                cfg_rdw_p->cfg_val = pci_read_config(sc->dev, cfg_rdw_p->cfg_id,
                                         cfg_rdw_p->cfg_width);

            } else if(cfg_rdw_p->cfg_cmd == BXE_WRITE_PCICFG) {
                pci_write_config(sc->dev, cfg_rdw_p->cfg_id, cfg_rdw_p->cfg_val,
                            cfg_rdw_p->cfg_width);
            } else {
                BLOGW(sc, "BXE_RDW_PCICFG ioctl wrong cmd passed\n");
            }
            break;

        case BXE_MAC_ADDR:
            mac_addr_p = (bxe_perm_mac_addr_t *)data;
            snprintf(mac_addr_p->mac_addr_str, sizeof(sc->mac_addr_str), "%s",
                sc->mac_addr_str);
            break;

        case BXE_EEPROM:
            rval = bxe_eeprom_rd_wr(sc, (bxe_eeprom_t *)data);
            break;


        default:
            break;
    }

    return (rval);
}