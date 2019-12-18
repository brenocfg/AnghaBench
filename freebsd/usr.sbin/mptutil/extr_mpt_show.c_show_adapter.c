#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int U16 ;
struct TYPE_8__ {int PageLength; } ;
struct TYPE_9__ {char* BoardName; char* BoardAssembly; char* ChipName; char* ChipRevision; int CapabilitiesFlags; int MinDrivesIS; int MaxDrivesIS; int MinDrivesIM; int MaxDrivesIM; int MinDrivesIME; int MaxDrivesIME; int /*<<< orphan*/  SupportedStripeSizeMapIME; int /*<<< orphan*/  SupportedStripeSizeMapIS; TYPE_1__ Header; } ;
typedef  TYPE_2__ CONFIG_PAGE_MANUFACTURING_0 ;
typedef  TYPE_2__ CONFIG_PAGE_IOC_6 ;
typedef  TYPE_2__ CONFIG_PAGE_IOC_2 ;

/* Variables and functions */
 int EINVAL ; 
 int MPI_IOCPAGE2_CAP_FLAGS_IME_SUPPORT ; 
 int MPI_IOCPAGE2_CAP_FLAGS_IM_SUPPORT ; 
 int MPI_IOCPAGE2_CAP_FLAGS_IS_SUPPORT ; 
 int MPI_IOCPAGE2_CAP_FLAGS_RAID_10_SUPPORT ; 
 int MPI_IOCPAGE2_CAP_FLAGS_RAID_50_SUPPORT ; 
 int MPI_IOCPAGE2_CAP_FLAGS_RAID_5_SUPPORT ; 
 int MPI_IOCPAGE2_CAP_FLAGS_RAID_6_SUPPORT ; 
 int MPI_IOCSTATUS_CONFIG_INVALID_PAGE ; 
 int MPI_IOCSTATUS_MASK ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  display_stripe_map (char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  mpt_ioc_status (int) ; 
 int mpt_open (int) ; 
 TYPE_2__* mpt_read_ioc_page (int,int,int*) ; 
 TYPE_2__* mpt_read_man_page (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mpt_unit ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
show_adapter(int ac, char **av)
{
	CONFIG_PAGE_MANUFACTURING_0 *man0;
	CONFIG_PAGE_IOC_2 *ioc2;
	CONFIG_PAGE_IOC_6 *ioc6;
	U16 IOCStatus;
	int comma, error, fd;

	if (ac != 1) {
		warnx("show adapter: extra arguments");
		return (EINVAL);
	}

	fd = mpt_open(mpt_unit);
	if (fd < 0) {
		error = errno;
		warn("mpt_open");
		return (error);
	}

	man0 = mpt_read_man_page(fd, 0, NULL);
	if (man0 == NULL) {
		error = errno;
		warn("Failed to get controller info");
		close(fd);
		return (error);
	}
	if (man0->Header.PageLength < sizeof(*man0) / 4) {
		warnx("Invalid controller info");
		free(man0);
		close(fd);
		return (EINVAL);
	}
	printf("mpt%d Adapter:\n", mpt_unit);
	printf("       Board Name: %.16s\n", man0->BoardName);
	printf("   Board Assembly: %.16s\n", man0->BoardAssembly);
	printf("        Chip Name: %.16s\n", man0->ChipName);
	printf("    Chip Revision: %.16s\n", man0->ChipRevision);

	free(man0);

	ioc2 = mpt_read_ioc_page(fd, 2, &IOCStatus);
	if (ioc2 != NULL) {
		printf("      RAID Levels:");
		comma = 0;
		if (ioc2->CapabilitiesFlags &
		    MPI_IOCPAGE2_CAP_FLAGS_IS_SUPPORT) {
			printf(" RAID0");
			comma = 1;
		}
		if (ioc2->CapabilitiesFlags &
		    MPI_IOCPAGE2_CAP_FLAGS_IM_SUPPORT) {
			printf("%s RAID1", comma ? "," : "");
			comma = 1;
		}
		if (ioc2->CapabilitiesFlags &
		    MPI_IOCPAGE2_CAP_FLAGS_IME_SUPPORT) {
			printf("%s RAID1E", comma ? "," : "");
			comma = 1;
		}
		if (ioc2->CapabilitiesFlags &
		    MPI_IOCPAGE2_CAP_FLAGS_RAID_5_SUPPORT) {
			printf("%s RAID5", comma ? "," : "");
			comma = 1;
		}
		if (ioc2->CapabilitiesFlags &
		    MPI_IOCPAGE2_CAP_FLAGS_RAID_6_SUPPORT) {
			printf("%s RAID6", comma ? "," : "");
			comma = 1;
		}
		if (ioc2->CapabilitiesFlags &
		    MPI_IOCPAGE2_CAP_FLAGS_RAID_10_SUPPORT) {
			printf("%s RAID10", comma ? "," : "");
			comma = 1;
		}
		if (ioc2->CapabilitiesFlags &
		    MPI_IOCPAGE2_CAP_FLAGS_RAID_50_SUPPORT) {
			printf("%s RAID50", comma ? "," : "");
			comma = 1;
		}
		if (!comma)
			printf(" none");
		printf("\n");
		free(ioc2);
	} else if ((IOCStatus & MPI_IOCSTATUS_MASK) !=
	    MPI_IOCSTATUS_CONFIG_INVALID_PAGE)
		warnx("mpt_read_ioc_page(2): %s", mpt_ioc_status(IOCStatus));

	ioc6 = mpt_read_ioc_page(fd, 6, &IOCStatus);
	if (ioc6 != NULL) {
		display_stripe_map("    RAID0 Stripes",
		    ioc6->SupportedStripeSizeMapIS);
		display_stripe_map("   RAID1E Stripes",
		    ioc6->SupportedStripeSizeMapIME);
		printf(" RAID0 Drives/Vol: %u", ioc6->MinDrivesIS);
		if (ioc6->MinDrivesIS != ioc6->MaxDrivesIS)
			printf("-%u", ioc6->MaxDrivesIS);
		printf("\n");
		printf(" RAID1 Drives/Vol: %u", ioc6->MinDrivesIM);
		if (ioc6->MinDrivesIM != ioc6->MaxDrivesIM)
			printf("-%u", ioc6->MaxDrivesIM);
		printf("\n");
		printf("RAID1E Drives/Vol: %u", ioc6->MinDrivesIME);
		if (ioc6->MinDrivesIME != ioc6->MaxDrivesIME)
			printf("-%u", ioc6->MaxDrivesIME);
		printf("\n");
		free(ioc6);
	} else if ((IOCStatus & MPI_IOCSTATUS_MASK) !=
	    MPI_IOCSTATUS_CONFIG_INVALID_PAGE)
		warnx("mpt_read_ioc_page(6): %s", mpt_ioc_status(IOCStatus));

	/* TODO: Add an ioctl to fetch IOC_FACTS and print firmware version. */

	close(fd);

	return (0);
}