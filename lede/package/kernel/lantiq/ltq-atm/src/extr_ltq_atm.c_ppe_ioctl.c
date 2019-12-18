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
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct atm_dev {int dummy; } ;
typedef  int /*<<< orphan*/  mib_vcc ;
typedef  int /*<<< orphan*/  mib_cell ;
typedef  int /*<<< orphan*/  mib_aal5 ;
struct TYPE_14__ {int /*<<< orphan*/  aal5VccSarTimeOuts; int /*<<< orphan*/  aal5VccOverSizedSDUs; int /*<<< orphan*/  aal5VccCrcErrors; } ;
struct TYPE_15__ {TYPE_2__ mib_vcc; int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; int /*<<< orphan*/  ifOutDiscards; int /*<<< orphan*/  ifOutErros; scalar_t__ ifInDiscards; int /*<<< orphan*/  ifInErrors; int /*<<< orphan*/  ifOutUcastPkts; int /*<<< orphan*/  ifInUcastPkts; int /*<<< orphan*/  ifHCOutOctets_l; int /*<<< orphan*/  ifHCOutOctets_h; int /*<<< orphan*/  ifHCInOctets_l; int /*<<< orphan*/  ifHCInOctets_h; int /*<<< orphan*/  ifOutErrors; int /*<<< orphan*/  ifInUnknownProtos; } ;
typedef  TYPE_3__ atm_cell_ifEntry_t ;
typedef  TYPE_3__ atm_aal5_vcc_x_t ;
typedef  TYPE_3__ atm_aal5_ifEntry_t ;
struct TYPE_16__ {int /*<<< orphan*/  l; int /*<<< orphan*/  h; } ;
struct TYPE_17__ {unsigned int prev_wrx_total_byte; unsigned int prev_wtx_total_byte; TYPE_1__* conn; int /*<<< orphan*/  wtx_drop_pdu; int /*<<< orphan*/  wtx_err_pdu; scalar_t__ wrx_drop_pdu; int /*<<< orphan*/  wrx_pdu; TYPE_6__ wtx_total_byte; TYPE_6__ wrx_total_byte; } ;
struct TYPE_13__ {int /*<<< orphan*/  aal5_vcc_oversize_sdu; int /*<<< orphan*/  aal5_vcc_crc_err; } ;
struct TYPE_12__ {unsigned int wrx_total_byte; unsigned int wtx_total_byte; scalar_t__ wrx_dropdes_pdu; int /*<<< orphan*/  wrx_err_pdu; int /*<<< orphan*/  wtx_total_pdu; int /*<<< orphan*/  wrx_drophtu_cell; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int ENOTTY ; 
 scalar_t__ PPE_ATM_IOC_MAGIC ; 
 scalar_t__ PPE_ATM_IOC_MAXNR ; 
#define  PPE_ATM_MIB_AAL5 130 
#define  PPE_ATM_MIB_CELL 129 
#define  PPE_ATM_MIB_VCC 128 
 int /*<<< orphan*/  VERIFY_READ ; 
 int /*<<< orphan*/  VERIFY_WRITE ; 
 TYPE_11__* WAN_MIB_TABLE ; 
 int _IOC_DIR (unsigned int) ; 
 scalar_t__ _IOC_NR (unsigned int) ; 
 int _IOC_READ ; 
 int /*<<< orphan*/  _IOC_SIZE (unsigned int) ; 
 scalar_t__ _IOC_TYPE (unsigned int) ; 
 int _IOC_WRITE ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (TYPE_3__*,void*,int) ; 
 int /*<<< orphan*/  copy_to_user (void*,TYPE_3__*,int) ; 
 int find_vpivci (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ g_atm_priv_data ; 
 int /*<<< orphan*/  u64_add_u32 (TYPE_6__,int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static int ppe_ioctl(struct atm_dev *dev, unsigned int cmd, void *arg)
{
	int ret = 0;
	atm_cell_ifEntry_t mib_cell;
	atm_aal5_ifEntry_t mib_aal5;
	atm_aal5_vcc_x_t mib_vcc;
	unsigned int value;
	int conn;

	if ( _IOC_TYPE(cmd) != PPE_ATM_IOC_MAGIC
			|| _IOC_NR(cmd) >= PPE_ATM_IOC_MAXNR )
		return -ENOTTY;

	if ( _IOC_DIR(cmd) & _IOC_READ )
		ret = !access_ok(VERIFY_WRITE, arg, _IOC_SIZE(cmd));
	else if ( _IOC_DIR(cmd) & _IOC_WRITE )
		ret = !access_ok(VERIFY_READ, arg, _IOC_SIZE(cmd));
	if ( ret )
		return -EFAULT;

	switch (cmd) {
	case PPE_ATM_MIB_CELL:  /*  cell level  MIB */
		/*  These MIB should be read at ARC side, now put zero only.    */
		mib_cell.ifHCInOctets_h = 0;
		mib_cell.ifHCInOctets_l = 0;
		mib_cell.ifHCOutOctets_h = 0;
		mib_cell.ifHCOutOctets_l = 0;
		mib_cell.ifInErrors = 0;
		mib_cell.ifInUnknownProtos = WAN_MIB_TABLE->wrx_drophtu_cell;
		mib_cell.ifOutErrors = 0;

		ret = sizeof(mib_cell) - copy_to_user(arg, &mib_cell, sizeof(mib_cell));
		break;

	case PPE_ATM_MIB_AAL5:  /*  AAL5 MIB    */
		value = WAN_MIB_TABLE->wrx_total_byte;
		u64_add_u32(g_atm_priv_data.wrx_total_byte, value - g_atm_priv_data.prev_wrx_total_byte, &g_atm_priv_data.wrx_total_byte);
		g_atm_priv_data.prev_wrx_total_byte = value;
		mib_aal5.ifHCInOctets_h = g_atm_priv_data.wrx_total_byte.h;
		mib_aal5.ifHCInOctets_l = g_atm_priv_data.wrx_total_byte.l;

		value = WAN_MIB_TABLE->wtx_total_byte;
		u64_add_u32(g_atm_priv_data.wtx_total_byte, value - g_atm_priv_data.prev_wtx_total_byte, &g_atm_priv_data.wtx_total_byte);
		g_atm_priv_data.prev_wtx_total_byte = value;
		mib_aal5.ifHCOutOctets_h = g_atm_priv_data.wtx_total_byte.h;
		mib_aal5.ifHCOutOctets_l = g_atm_priv_data.wtx_total_byte.l;

		mib_aal5.ifInUcastPkts  = g_atm_priv_data.wrx_pdu;
		mib_aal5.ifOutUcastPkts = WAN_MIB_TABLE->wtx_total_pdu;
		mib_aal5.ifInErrors     = WAN_MIB_TABLE->wrx_err_pdu;
		mib_aal5.ifInDiscards   = WAN_MIB_TABLE->wrx_dropdes_pdu + g_atm_priv_data.wrx_drop_pdu;
		mib_aal5.ifOutErros     = g_atm_priv_data.wtx_err_pdu;
		mib_aal5.ifOutDiscards  = g_atm_priv_data.wtx_drop_pdu;

		ret = sizeof(mib_aal5) - copy_to_user(arg, &mib_aal5, sizeof(mib_aal5));
		break;

	case PPE_ATM_MIB_VCC:   /*  VCC related MIB */
		copy_from_user(&mib_vcc, arg, sizeof(mib_vcc));
		conn = find_vpivci(mib_vcc.vpi, mib_vcc.vci);
		if (conn >= 0) {
			mib_vcc.mib_vcc.aal5VccCrcErrors     = g_atm_priv_data.conn[conn].aal5_vcc_crc_err;
			mib_vcc.mib_vcc.aal5VccOverSizedSDUs = g_atm_priv_data.conn[conn].aal5_vcc_oversize_sdu;
			mib_vcc.mib_vcc.aal5VccSarTimeOuts   = 0;   /*  no timer support    */
			ret = sizeof(mib_vcc) - copy_to_user(arg, &mib_vcc, sizeof(mib_vcc));
		} else
			ret = -EINVAL;
		break;

	default:
		ret = -ENOIOCTLCMD;
	}

	return ret;
}