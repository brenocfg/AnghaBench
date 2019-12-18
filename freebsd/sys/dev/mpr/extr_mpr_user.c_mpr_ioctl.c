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
struct mpr_usr_command {int dummy; } ;
struct mpr_softc {int /*<<< orphan*/  mpr_mtx; int /*<<< orphan*/  port_enable_complete; } ;
struct mpr_ext_cfg_page_req {int len; int /*<<< orphan*/  buf; } ;
struct mpr_cfg_page_req {int len; int /*<<< orphan*/  buf; } ;
struct cdev {struct mpr_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  mpr_reg_access_t ;
typedef  int /*<<< orphan*/  mpr_pci_info_t ;
typedef  int /*<<< orphan*/  mpr_pass_thru_t ;
typedef  int /*<<< orphan*/  mpr_event_report_t ;
typedef  int /*<<< orphan*/  mpr_event_query_t ;
typedef  int /*<<< orphan*/  mpr_event_enable_t ;
typedef  int /*<<< orphan*/  mpr_diag_action_t ;
typedef  int /*<<< orphan*/  mpr_btdh_mapping_t ;
typedef  int /*<<< orphan*/  mpr_adapter_data_t ;
typedef  int /*<<< orphan*/  MPI2_CONFIG_PAGE_HEADER ;
typedef  int /*<<< orphan*/  MPI2_CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int ENOIOCTL ; 
#define  MPRIO_MPR_COMMAND 143 
#define  MPRIO_READ_CFG_HEADER 142 
#define  MPRIO_READ_CFG_PAGE 141 
#define  MPRIO_READ_EXT_CFG_HEADER 140 
#define  MPRIO_READ_EXT_CFG_PAGE 139 
#define  MPRIO_WRITE_CFG_PAGE 138 
 int /*<<< orphan*/  MPR_USER ; 
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
 int /*<<< orphan*/  M_MPRUSER ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PRIBIO ; 
 int copyin (int /*<<< orphan*/ ,void*,int) ; 
 int copyout (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int hz ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mpr_lock (struct mpr_softc*) ; 
 int mpr_reinit (struct mpr_softc*) ; 
 int /*<<< orphan*/  mpr_unlock (struct mpr_softc*) ; 
 int mpr_user_btdh (struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int mpr_user_command (struct mpr_softc*,struct mpr_usr_command*) ; 
 int mpr_user_diag_action (struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpr_user_event_enable (struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpr_user_event_query (struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int mpr_user_event_report (struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpr_user_get_adapter_data (struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int mpr_user_pass_thru (struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int mpr_user_read_cfg_header (struct mpr_softc*,struct mpr_cfg_page_req*) ; 
 int mpr_user_read_cfg_page (struct mpr_softc*,struct mpr_cfg_page_req*,void*) ; 
 int mpr_user_read_extcfg_header (struct mpr_softc*,struct mpr_ext_cfg_page_req*) ; 
 int mpr_user_read_extcfg_page (struct mpr_softc*,struct mpr_ext_cfg_page_req*,void*) ; 
 int /*<<< orphan*/  mpr_user_read_pci_info (struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int mpr_user_reg_access (struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int mpr_user_write_cfg_page (struct mpr_softc*,struct mpr_cfg_page_req*,void*) ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static int
mpr_ioctl(struct cdev *dev, u_long cmd, void *arg, int flag,
    struct thread *td)
{
	struct mpr_softc *sc;
	struct mpr_cfg_page_req *page_req;
	struct mpr_ext_cfg_page_req *ext_page_req;
	void *mpr_page;
	int error, msleep_ret;

	mpr_page = NULL;
	sc = dev->si_drv1;
	page_req = (void *)arg;
	ext_page_req = (void *)arg;

	switch (cmd) {
	case MPRIO_READ_CFG_HEADER:
		mpr_lock(sc);
		error = mpr_user_read_cfg_header(sc, page_req);
		mpr_unlock(sc);
		break;
	case MPRIO_READ_CFG_PAGE:
		mpr_page = malloc(page_req->len, M_MPRUSER, M_WAITOK | M_ZERO);
		error = copyin(page_req->buf, mpr_page,
		    sizeof(MPI2_CONFIG_PAGE_HEADER));
		if (error)
			break;
		mpr_lock(sc);
		error = mpr_user_read_cfg_page(sc, page_req, mpr_page);
		mpr_unlock(sc);
		if (error)
			break;
		error = copyout(mpr_page, page_req->buf, page_req->len);
		break;
	case MPRIO_READ_EXT_CFG_HEADER:
		mpr_lock(sc);
		error = mpr_user_read_extcfg_header(sc, ext_page_req);
		mpr_unlock(sc);
		break;
	case MPRIO_READ_EXT_CFG_PAGE:
		mpr_page = malloc(ext_page_req->len, M_MPRUSER,
		    M_WAITOK | M_ZERO);
		error = copyin(ext_page_req->buf, mpr_page,
		    sizeof(MPI2_CONFIG_EXTENDED_PAGE_HEADER));
		if (error)
			break;
		mpr_lock(sc);
		error = mpr_user_read_extcfg_page(sc, ext_page_req, mpr_page);
		mpr_unlock(sc);
		if (error)
			break;
		error = copyout(mpr_page, ext_page_req->buf, ext_page_req->len);
		break;
	case MPRIO_WRITE_CFG_PAGE:
		mpr_page = malloc(page_req->len, M_MPRUSER, M_WAITOK|M_ZERO);
		error = copyin(page_req->buf, mpr_page, page_req->len);
		if (error)
			break;
		mpr_lock(sc);
		error = mpr_user_write_cfg_page(sc, page_req, mpr_page);
		mpr_unlock(sc);
		break;
	case MPRIO_MPR_COMMAND:
		error = mpr_user_command(sc, (struct mpr_usr_command *)arg);
		break;
	case MPTIOCTL_PASS_THRU:
		/*
		 * The user has requested to pass through a command to be
		 * executed by the MPT firmware.  Call our routine which does
		 * this.  Only allow one passthru IOCTL at one time.
		 */
		error = mpr_user_pass_thru(sc, (mpr_pass_thru_t *)arg);
		break;
	case MPTIOCTL_GET_ADAPTER_DATA:
		/*
		 * The user has requested to read adapter data.  Call our
		 * routine which does this.
		 */
		error = 0;
		mpr_user_get_adapter_data(sc, (mpr_adapter_data_t *)arg);
		break;
	case MPTIOCTL_GET_PCI_INFO:
		/*
		 * The user has requested to read pci info.  Call
		 * our routine which does this.
		 */
		mpr_lock(sc);
		error = 0;
		mpr_user_read_pci_info(sc, (mpr_pci_info_t *)arg);
		mpr_unlock(sc);
		break;
	case MPTIOCTL_RESET_ADAPTER:
		mpr_lock(sc);
		sc->port_enable_complete = 0;
		uint32_t reinit_start = time_uptime;
		error = mpr_reinit(sc);
		/* Sleep for 300 second. */
		msleep_ret = msleep(&sc->port_enable_complete, &sc->mpr_mtx,
		    PRIBIO, "mpr_porten", 300 * hz);
		mpr_unlock(sc);
		if (msleep_ret)
			printf("Port Enable did not complete after Diag "
			    "Reset msleep error %d.\n", msleep_ret);
		else
			mpr_dprint(sc, MPR_USER, "Hard Reset with Port Enable "
			    "completed in %d seconds.\n",
			    (uint32_t)(time_uptime - reinit_start));
		break;
	case MPTIOCTL_DIAG_ACTION:
		/*
		 * The user has done a diag buffer action.  Call our routine
		 * which does this.  Only allow one diag action at one time.
		 */
		mpr_lock(sc);
		error = mpr_user_diag_action(sc, (mpr_diag_action_t *)arg);
		mpr_unlock(sc);
		break;
	case MPTIOCTL_EVENT_QUERY:
		/*
		 * The user has done an event query. Call our routine which does
		 * this.
		 */
		error = 0;
		mpr_user_event_query(sc, (mpr_event_query_t *)arg);
		break;
	case MPTIOCTL_EVENT_ENABLE:
		/*
		 * The user has done an event enable. Call our routine which
		 * does this.
		 */
		error = 0;
		mpr_user_event_enable(sc, (mpr_event_enable_t *)arg);
		break;
	case MPTIOCTL_EVENT_REPORT:
		/*
		 * The user has done an event report. Call our routine which
		 * does this.
		 */
		error = mpr_user_event_report(sc, (mpr_event_report_t *)arg);
		break;
	case MPTIOCTL_REG_ACCESS:
		/*
		 * The user has requested register access.  Call our routine
		 * which does this.
		 */
		mpr_lock(sc);
		error = mpr_user_reg_access(sc, (mpr_reg_access_t *)arg);
		mpr_unlock(sc);
		break;
	case MPTIOCTL_BTDH_MAPPING:
		/*
		 * The user has requested to translate a bus/target to a
		 * DevHandle or a DevHandle to a bus/target.  Call our routine
		 * which does this.
		 */
		error = mpr_user_btdh(sc, (mpr_btdh_mapping_t *)arg);
		break;
	default:
		error = ENOIOCTL;
		break;
	}

	if (mpr_page != NULL)
		free(mpr_page, M_MPRUSER);

	return (error);
}