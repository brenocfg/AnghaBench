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
union aac_statrequest {size_t as_item; int /*<<< orphan*/  as_qstat; } ;
typedef  int u_long ;
struct thread {int dummy; } ;
struct cdev {struct aac_softc* si_drv1; } ;
struct aac_softc {int /*<<< orphan*/ * aac_qstat; } ;
struct aac_qstat {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  AACIO_STATS 155 
#define  AACQ_BUSY 154 
#define  AACQ_FREE 153 
#define  AACQ_READY 152 
 int EINVAL ; 
 int ENOENT ; 
#define  FSACTL_AIF_THREAD 151 
#define  FSACTL_CLOSE_GET_ADAPTER_FIB 150 
#define  FSACTL_DELETE_DISK 149 
#define  FSACTL_GET_FEATURES 148 
#define  FSACTL_GET_NEXT_ADAPTER_FIB 147 
#define  FSACTL_GET_PCI_INFO 146 
#define  FSACTL_LNX_AIF_THREAD 145 
#define  FSACTL_LNX_CLOSE_GET_ADAPTER_FIB 144 
#define  FSACTL_LNX_DELETE_DISK 143 
#define  FSACTL_LNX_GET_FEATURES 142 
#define  FSACTL_LNX_GET_NEXT_ADAPTER_FIB 141 
#define  FSACTL_LNX_GET_PCI_INFO 140 
#define  FSACTL_LNX_MINIPORT_REV_CHECK 139 
#define  FSACTL_LNX_OPEN_GET_ADAPTER_FIB 138 
#define  FSACTL_LNX_QUERY_DISK 137 
#define  FSACTL_LNX_SENDFIB 136 
#define  FSACTL_LNX_SEND_LARGE_FIB 135 
#define  FSACTL_LNX_SEND_RAW_SRB 134 
#define  FSACTL_MINIPORT_REV_CHECK 133 
#define  FSACTL_OPEN_GET_ADAPTER_FIB 132 
#define  FSACTL_QUERY_DISK 131 
#define  FSACTL_SENDFIB 130 
#define  FSACTL_SEND_LARGE_FIB 129 
#define  FSACTL_SEND_RAW_SRB 128 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 char* HBA_FLAGS_DBG_IOCTL_COMMANDS_B ; 
 int aac_close_aif (struct aac_softc*,scalar_t__) ; 
 int aac_get_pci_info (struct aac_softc*,scalar_t__) ; 
 int aac_getnext_aif (struct aac_softc*,scalar_t__) ; 
 int aac_ioctl_send_raw_srb (struct aac_softc*,scalar_t__) ; 
 int aac_ioctl_sendfib (struct aac_softc*,scalar_t__) ; 
 int aac_open_aif (struct aac_softc*,scalar_t__) ; 
 int aac_query_disk (struct aac_softc*,scalar_t__) ; 
 int aac_rev_check (struct aac_softc*,scalar_t__) ; 
 int aac_supported_features (struct aac_softc*,scalar_t__) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*,...) ; 

__attribute__((used)) static int
aac_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int flag, struct thread *td)
{
	union aac_statrequest *as;
	struct aac_softc *sc;
	int error = 0;

	as = (union aac_statrequest *)arg;
	sc = dev->si_drv1;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	switch (cmd) {
	case AACIO_STATS:
		switch (as->as_item) {
		case AACQ_FREE:
		case AACQ_READY:
		case AACQ_BUSY:
			bcopy(&sc->aac_qstat[as->as_item], &as->as_qstat,
			      sizeof(struct aac_qstat));
			break;
		default:
			error = ENOENT;
			break;
		}
	break;

	case FSACTL_SENDFIB:
	case FSACTL_SEND_LARGE_FIB:
		arg = *(caddr_t*)arg;
	case FSACTL_LNX_SENDFIB:
	case FSACTL_LNX_SEND_LARGE_FIB:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_SENDFIB");
		error = aac_ioctl_sendfib(sc, arg);
		break;
	case FSACTL_SEND_RAW_SRB:
		arg = *(caddr_t*)arg;
	case FSACTL_LNX_SEND_RAW_SRB:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_SEND_RAW_SRB");
		error = aac_ioctl_send_raw_srb(sc, arg);
		break;
	case FSACTL_AIF_THREAD:
	case FSACTL_LNX_AIF_THREAD:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_AIF_THREAD");
		error = EINVAL;
		break;
	case FSACTL_OPEN_GET_ADAPTER_FIB:
		arg = *(caddr_t*)arg;
	case FSACTL_LNX_OPEN_GET_ADAPTER_FIB:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_OPEN_GET_ADAPTER_FIB");
		error = aac_open_aif(sc, arg);
		break;
	case FSACTL_GET_NEXT_ADAPTER_FIB:
		arg = *(caddr_t*)arg;
	case FSACTL_LNX_GET_NEXT_ADAPTER_FIB:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_GET_NEXT_ADAPTER_FIB");
		error = aac_getnext_aif(sc, arg);
		break;
	case FSACTL_CLOSE_GET_ADAPTER_FIB:
		arg = *(caddr_t*)arg;
	case FSACTL_LNX_CLOSE_GET_ADAPTER_FIB:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_CLOSE_GET_ADAPTER_FIB");
		error = aac_close_aif(sc, arg);
		break;
	case FSACTL_MINIPORT_REV_CHECK:
		arg = *(caddr_t*)arg;
	case FSACTL_LNX_MINIPORT_REV_CHECK:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_MINIPORT_REV_CHECK");
		error = aac_rev_check(sc, arg);
		break;
	case FSACTL_QUERY_DISK:
		arg = *(caddr_t*)arg;
	case FSACTL_LNX_QUERY_DISK:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_QUERY_DISK");
		error = aac_query_disk(sc, arg);
		break;
	case FSACTL_DELETE_DISK:
	case FSACTL_LNX_DELETE_DISK:
		/*
		 * We don't trust the underland to tell us when to delete a
		 * container, rather we rely on an AIF coming from the
		 * controller
		 */
		error = 0;
		break;
	case FSACTL_GET_PCI_INFO:
		arg = *(caddr_t*)arg;
	case FSACTL_LNX_GET_PCI_INFO:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_GET_PCI_INFO");
		error = aac_get_pci_info(sc, arg);
		break;
	case FSACTL_GET_FEATURES:
		arg = *(caddr_t*)arg;
	case FSACTL_LNX_GET_FEATURES:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "FSACTL_GET_FEATURES");
		error = aac_supported_features(sc, arg);
		break;
	default:
		fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "unsupported cmd 0x%lx\n", cmd);
		error = EINVAL;
		break;
	}
	return(error);
}