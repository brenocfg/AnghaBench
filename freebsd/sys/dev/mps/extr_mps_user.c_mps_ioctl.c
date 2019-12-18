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
typedef  scalar_t__ uint32_t ;
typedef  int u_long ;
struct thread {int dummy; } ;
struct mps_usr_command {int dummy; } ;
struct mps_softc {int /*<<< orphan*/  mps_mtx; int /*<<< orphan*/  port_enable_complete; } ;
struct mps_ext_cfg_page_req {int len; int /*<<< orphan*/  buf; } ;
struct mps_cfg_page_req {int len; int /*<<< orphan*/  buf; } ;
struct cdev {struct mps_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  mps_reg_access_t ;
typedef  int /*<<< orphan*/  mps_pci_info_t ;
typedef  int /*<<< orphan*/  mps_pass_thru_t ;
typedef  int /*<<< orphan*/  mps_event_report_t ;
typedef  int /*<<< orphan*/  mps_event_query_t ;
typedef  int /*<<< orphan*/  mps_event_enable_t ;
typedef  int /*<<< orphan*/  mps_diag_action_t ;
typedef  int /*<<< orphan*/  mps_btdh_mapping_t ;
typedef  int /*<<< orphan*/  mps_adapter_data_t ;
typedef  int /*<<< orphan*/  MPI2_CONFIG_PAGE_HEADER ;
typedef  int /*<<< orphan*/  MPI2_CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int ENOIOCTL ; 
#define  MPSIO_MPS_COMMAND 143 
#define  MPSIO_READ_CFG_HEADER 142 
#define  MPSIO_READ_CFG_PAGE 141 
#define  MPSIO_READ_EXT_CFG_HEADER 140 
#define  MPSIO_READ_EXT_CFG_PAGE 139 
#define  MPSIO_WRITE_CFG_PAGE 138 
 int /*<<< orphan*/  MPS_USER ; 
#define  MPTIOCTL_BTDH_MAPPING 137 
#define  MPTIOCTL_DIAG_ACTION 136 
#define  MPTIOCTL_EVENT_ENABLE 135 
#define  MPTIOCTL_EVENT_QUERY 134 
#define  MPTIOCTL_EVENT_REPORT 133 
#define  MPTIOCTL_GET_ADAPTER_DATA 132 
#define  MPTIOCTL_GET_PCI_INFO 131 
#define  MPTIOCTL_PASS_THRU 130 
#define  MPTIOCTL_REG_ACCESS 129 
#define  MPTIOCTL_RESET_ADAPTER 128 
 int /*<<< orphan*/  M_MPSUSER ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PRIBIO ; 
 int copyin (int /*<<< orphan*/ ,void*,int) ; 
 int copyout (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int hz ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mps_dprint (struct mps_softc*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mps_lock (struct mps_softc*) ; 
 int mps_reinit (struct mps_softc*) ; 
 int /*<<< orphan*/  mps_unlock (struct mps_softc*) ; 
 int mps_user_btdh (struct mps_softc*,int /*<<< orphan*/ *) ; 
 int mps_user_command (struct mps_softc*,struct mps_usr_command*) ; 
 int mps_user_diag_action (struct mps_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mps_user_event_enable (struct mps_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mps_user_event_query (struct mps_softc*,int /*<<< orphan*/ *) ; 
 int mps_user_event_report (struct mps_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mps_user_get_adapter_data (struct mps_softc*,int /*<<< orphan*/ *) ; 
 int mps_user_pass_thru (struct mps_softc*,int /*<<< orphan*/ *) ; 
 int mps_user_read_cfg_header (struct mps_softc*,struct mps_cfg_page_req*) ; 
 int mps_user_read_cfg_page (struct mps_softc*,struct mps_cfg_page_req*,void*) ; 
 int mps_user_read_extcfg_header (struct mps_softc*,struct mps_ext_cfg_page_req*) ; 
 int mps_user_read_extcfg_page (struct mps_softc*,struct mps_ext_cfg_page_req*,void*) ; 
 int /*<<< orphan*/  mps_user_read_pci_info (struct mps_softc*,int /*<<< orphan*/ *) ; 
 int mps_user_reg_access (struct mps_softc*,int /*<<< orphan*/ *) ; 
 int mps_user_write_cfg_page (struct mps_softc*,struct mps_cfg_page_req*,void*) ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static int
mps_ioctl(struct cdev *dev, u_long cmd, void *arg, int flag,
    struct thread *td)
{
	struct mps_softc *sc;
	struct mps_cfg_page_req *page_req;
	struct mps_ext_cfg_page_req *ext_page_req;
	void *mps_page;
	int error, msleep_ret;

	mps_page = NULL;
	sc = dev->si_drv1;
	page_req = (void *)arg;
	ext_page_req = (void *)arg;

	switch (cmd) {
	case MPSIO_READ_CFG_HEADER:
		mps_lock(sc);
		error = mps_user_read_cfg_header(sc, page_req);
		mps_unlock(sc);
		break;
	case MPSIO_READ_CFG_PAGE:
		mps_page = malloc(page_req->len, M_MPSUSER, M_WAITOK | M_ZERO);
		error = copyin(page_req->buf, mps_page,
		    sizeof(MPI2_CONFIG_PAGE_HEADER));
		if (error)
			break;
		mps_lock(sc);
		error = mps_user_read_cfg_page(sc, page_req, mps_page);
		mps_unlock(sc);
		if (error)
			break;
		error = copyout(mps_page, page_req->buf, page_req->len);
		break;
	case MPSIO_READ_EXT_CFG_HEADER:
		mps_lock(sc);
		error = mps_user_read_extcfg_header(sc, ext_page_req);
		mps_unlock(sc);
		break;
	case MPSIO_READ_EXT_CFG_PAGE:
		mps_page = malloc(ext_page_req->len, M_MPSUSER, M_WAITOK|M_ZERO);
		error = copyin(ext_page_req->buf, mps_page,
		    sizeof(MPI2_CONFIG_EXTENDED_PAGE_HEADER));
		if (error)
			break;
		mps_lock(sc);
		error = mps_user_read_extcfg_page(sc, ext_page_req, mps_page);
		mps_unlock(sc);
		if (error)
			break;
		error = copyout(mps_page, ext_page_req->buf, ext_page_req->len);
		break;
	case MPSIO_WRITE_CFG_PAGE:
		mps_page = malloc(page_req->len, M_MPSUSER, M_WAITOK|M_ZERO);
		error = copyin(page_req->buf, mps_page, page_req->len);
		if (error)
			break;
		mps_lock(sc);
		error = mps_user_write_cfg_page(sc, page_req, mps_page);
		mps_unlock(sc);
		break;
	case MPSIO_MPS_COMMAND:
		error = mps_user_command(sc, (struct mps_usr_command *)arg);
		break;
	case MPTIOCTL_PASS_THRU:
		/*
		 * The user has requested to pass through a command to be
		 * executed by the MPT firmware.  Call our routine which does
		 * this.  Only allow one passthru IOCTL at one time.
		 */
		error = mps_user_pass_thru(sc, (mps_pass_thru_t *)arg);
		break;
	case MPTIOCTL_GET_ADAPTER_DATA:
		/*
		 * The user has requested to read adapter data.  Call our
		 * routine which does this.
		 */
		error = 0;
		mps_user_get_adapter_data(sc, (mps_adapter_data_t *)arg);
		break;
	case MPTIOCTL_GET_PCI_INFO:
		/*
		 * The user has requested to read pci info.  Call
		 * our routine which does this.
		 */
		mps_lock(sc);
		error = 0;
		mps_user_read_pci_info(sc, (mps_pci_info_t *)arg);
		mps_unlock(sc);
		break;
	case MPTIOCTL_RESET_ADAPTER:
		mps_lock(sc);
		sc->port_enable_complete = 0;
		uint32_t reinit_start = time_uptime;
		error = mps_reinit(sc);
		/* Sleep for 300 second. */
		msleep_ret = msleep(&sc->port_enable_complete, &sc->mps_mtx, PRIBIO,
		       "mps_porten", 300 * hz);
		mps_unlock(sc);
		if (msleep_ret)
			printf("Port Enable did not complete after Diag "
			    "Reset msleep error %d.\n", msleep_ret);
		else
			mps_dprint(sc, MPS_USER,
				"Hard Reset with Port Enable completed in %d seconds.\n",
				 (uint32_t) (time_uptime - reinit_start));
		break;
	case MPTIOCTL_DIAG_ACTION:
		/*
		 * The user has done a diag buffer action.  Call our routine
		 * which does this.  Only allow one diag action at one time.
		 */
		mps_lock(sc);
		error = mps_user_diag_action(sc, (mps_diag_action_t *)arg);
		mps_unlock(sc);
		break;
	case MPTIOCTL_EVENT_QUERY:
		/*
		 * The user has done an event query. Call our routine which does
		 * this.
		 */
		error = 0;
		mps_user_event_query(sc, (mps_event_query_t *)arg);
		break;
	case MPTIOCTL_EVENT_ENABLE:
		/*
		 * The user has done an event enable. Call our routine which
		 * does this.
		 */
		error = 0;
		mps_user_event_enable(sc, (mps_event_enable_t *)arg);
		break;
	case MPTIOCTL_EVENT_REPORT:
		/*
		 * The user has done an event report. Call our routine which
		 * does this.
		 */
		error = mps_user_event_report(sc, (mps_event_report_t *)arg);
		break;
	case MPTIOCTL_REG_ACCESS:
		/*
		 * The user has requested register access.  Call our routine
		 * which does this.
		 */
		mps_lock(sc);
		error = mps_user_reg_access(sc, (mps_reg_access_t *)arg);
		mps_unlock(sc);
		break;
	case MPTIOCTL_BTDH_MAPPING:
		/*
		 * The user has requested to translate a bus/target to a
		 * DevHandle or a DevHandle to a bus/target.  Call our routine
		 * which does this.
		 */
		error = mps_user_btdh(sc, (mps_btdh_mapping_t *)arg);
		break;
	default:
		error = ENOIOCTL;
		break;
	}

	if (mps_page != NULL)
		free(mps_page, M_MPSUSER);

	return (error);
}