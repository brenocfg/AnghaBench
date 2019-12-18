#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mpt_softc {int raid_max_volumes; size_t raid_page0_len; int raid_max_disks; TYPE_3__* ioc_page3; TYPE_4__* ioc_page2; int /*<<< orphan*/ * raid_disks; struct mpt_raid_volume* raid_volumes; } ;
struct mpt_raid_volume {int /*<<< orphan*/ * config_page; } ;
struct mpt_raid_disk {int dummy; } ;
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_8__ {int CapabilitiesFlags; int NumActiveVolumes; int MaxVolumes; int NumActivePhysDisks; int MaxPhysDisks; int /*<<< orphan*/  Header; } ;
struct TYPE_7__ {int /*<<< orphan*/  Header; } ;
struct TYPE_6__ {int PageLength; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageVersion; } ;
typedef  int /*<<< orphan*/  RAID_VOL0_PHYS_DISK ;
typedef  TYPE_1__ CONFIG_PAGE_HEADER ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_IOC ; 
#define  MPI_IOCPAGE2_CAP_FLAGS_CROSS_CHANNEL_SUPPORT 133 
#define  MPI_IOCPAGE2_CAP_FLAGS_IME_SUPPORT 132 
#define  MPI_IOCPAGE2_CAP_FLAGS_IM_SUPPORT 131 
#define  MPI_IOCPAGE2_CAP_FLAGS_IS_SUPPORT 130 
#define  MPI_IOCPAGE2_CAP_FLAGS_SAFTE_SUPPORT 129 
#define  MPI_IOCPAGE2_CAP_FLAGS_SES_SUPPORT 128 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mpt2host_config_page_ioc2 (TYPE_4__*) ; 
 int /*<<< orphan*/  mpt2host_config_page_ioc3 (TYPE_3__*) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 
 int /*<<< orphan*/  mpt_prtc (struct mpt_softc*,char*) ; 
 int /*<<< orphan*/  mpt_raid_free_mem (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_raid_wakeup (struct mpt_softc*) ; 
 int mpt_read_cfg_header (struct mpt_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mpt_read_cur_cfg_page (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mpt_read_config_info_ioc(struct mpt_softc *mpt)
{
	CONFIG_PAGE_HEADER hdr;
	struct mpt_raid_volume *mpt_raid;
	int rv;
	int i;
	size_t len;

	rv = mpt_read_cfg_header(mpt, MPI_CONFIG_PAGETYPE_IOC,
		2, 0, &hdr, FALSE, 5000);
	/*
	 * If it's an invalid page, so what? Not a supported function....
	 */
	if (rv == EINVAL) {
		return (0);
	}
	if (rv) {
		return (rv);
	}

	mpt_lprt(mpt, MPT_PRT_DEBUG,
	    "IOC Page 2 Header: Version %x len %x PageNumber %x PageType %x\n",
	    hdr.PageVersion, hdr.PageLength << 2,
	    hdr.PageNumber, hdr.PageType);

	len = hdr.PageLength * sizeof(uint32_t);
	mpt->ioc_page2 = malloc(len, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (mpt->ioc_page2 == NULL) {
		mpt_prt(mpt, "unable to allocate memory for IOC page 2\n");
		mpt_raid_free_mem(mpt);
		return (ENOMEM);
	}
	memcpy(&mpt->ioc_page2->Header, &hdr, sizeof(hdr));
	rv = mpt_read_cur_cfg_page(mpt, 0,
	    &mpt->ioc_page2->Header, len, FALSE, 5000);
	if (rv) {
		mpt_prt(mpt, "failed to read IOC Page 2\n");
		mpt_raid_free_mem(mpt);
		return (EIO);
	}
	mpt2host_config_page_ioc2(mpt->ioc_page2);

	if (mpt->ioc_page2->CapabilitiesFlags != 0) {
		uint32_t mask;

		mpt_prt(mpt, "Capabilities: (");
		for (mask = 1; mask != 0; mask <<= 1) {
			if ((mpt->ioc_page2->CapabilitiesFlags & mask) == 0) {
				continue;
			}
			switch (mask) {
			case MPI_IOCPAGE2_CAP_FLAGS_IS_SUPPORT:
				mpt_prtc(mpt, " RAID-0");
				break;
			case MPI_IOCPAGE2_CAP_FLAGS_IME_SUPPORT:
				mpt_prtc(mpt, " RAID-1E");
				break;
			case MPI_IOCPAGE2_CAP_FLAGS_IM_SUPPORT:
				mpt_prtc(mpt, " RAID-1");
				break;
			case MPI_IOCPAGE2_CAP_FLAGS_SES_SUPPORT:
				mpt_prtc(mpt, " SES");
				break;
			case MPI_IOCPAGE2_CAP_FLAGS_SAFTE_SUPPORT:
				mpt_prtc(mpt, " SAFTE");
				break;
			case MPI_IOCPAGE2_CAP_FLAGS_CROSS_CHANNEL_SUPPORT:
				mpt_prtc(mpt, " Multi-Channel-Arrays");
			default:
				break;
			}
		}
		mpt_prtc(mpt, " )\n");
		if ((mpt->ioc_page2->CapabilitiesFlags
		   & (MPI_IOCPAGE2_CAP_FLAGS_IS_SUPPORT
		    | MPI_IOCPAGE2_CAP_FLAGS_IME_SUPPORT
		    | MPI_IOCPAGE2_CAP_FLAGS_IM_SUPPORT)) != 0) {
			mpt_prt(mpt, "%d Active Volume%s(%d Max)\n",
				mpt->ioc_page2->NumActiveVolumes,
				mpt->ioc_page2->NumActiveVolumes != 1
			      ? "s " : " ",
				mpt->ioc_page2->MaxVolumes);
			mpt_prt(mpt, "%d Hidden Drive Member%s(%d Max)\n",
				mpt->ioc_page2->NumActivePhysDisks,
				mpt->ioc_page2->NumActivePhysDisks != 1
			      ? "s " : " ",
				mpt->ioc_page2->MaxPhysDisks);
		}
	}

	len = mpt->ioc_page2->MaxVolumes * sizeof(struct mpt_raid_volume);
	mpt->raid_volumes = malloc(len, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (mpt->raid_volumes == NULL) {
		mpt_prt(mpt, "Could not allocate RAID volume data\n");
		mpt_raid_free_mem(mpt);
		return (ENOMEM);
	}

	/*
	 * Copy critical data out of ioc_page2 so that we can
	 * safely refresh the page without windows of unreliable
	 * data.
	 */
	mpt->raid_max_volumes =  mpt->ioc_page2->MaxVolumes;

	len = sizeof(*mpt->raid_volumes->config_page) +
	    (sizeof (RAID_VOL0_PHYS_DISK) * (mpt->ioc_page2->MaxPhysDisks - 1));
	for (i = 0; i < mpt->ioc_page2->MaxVolumes; i++) {
		mpt_raid = &mpt->raid_volumes[i];
		mpt_raid->config_page =
		    malloc(len, M_DEVBUF, M_NOWAIT | M_ZERO);
		if (mpt_raid->config_page == NULL) {
			mpt_prt(mpt, "Could not allocate RAID page data\n");
			mpt_raid_free_mem(mpt);
			return (ENOMEM);
		}
	}
	mpt->raid_page0_len = len;

	len = mpt->ioc_page2->MaxPhysDisks * sizeof(struct mpt_raid_disk);
	mpt->raid_disks = malloc(len, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (mpt->raid_disks == NULL) {
		mpt_prt(mpt, "Could not allocate RAID disk data\n");
		mpt_raid_free_mem(mpt);
		return (ENOMEM);
	}
	mpt->raid_max_disks =  mpt->ioc_page2->MaxPhysDisks;

	/*
	 * Load page 3.
	 */
	rv = mpt_read_cfg_header(mpt, MPI_CONFIG_PAGETYPE_IOC,
	    3, 0, &hdr, FALSE, 5000);
	if (rv) {
		mpt_raid_free_mem(mpt);
		return (EIO);
	}

	mpt_lprt(mpt, MPT_PRT_DEBUG, "IOC Page 3 Header: %x %x %x %x\n",
	    hdr.PageVersion, hdr.PageLength, hdr.PageNumber, hdr.PageType);

	len = hdr.PageLength * sizeof(uint32_t);
	mpt->ioc_page3 = malloc(len, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (mpt->ioc_page3 == NULL) {
		mpt_prt(mpt, "unable to allocate memory for IOC page 3\n");
		mpt_raid_free_mem(mpt);
		return (ENOMEM);
	}
	memcpy(&mpt->ioc_page3->Header, &hdr, sizeof(hdr));
	rv = mpt_read_cur_cfg_page(mpt, 0,
	    &mpt->ioc_page3->Header, len, FALSE, 5000);
	if (rv) {
		mpt_raid_free_mem(mpt);
		return (EIO);
	}
	mpt2host_config_page_ioc3(mpt->ioc_page3);
	mpt_raid_wakeup(mpt);
	return (0);
}