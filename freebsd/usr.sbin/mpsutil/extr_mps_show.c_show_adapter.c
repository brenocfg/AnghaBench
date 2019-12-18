#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_16__ {int Word; } ;
struct TYPE_15__ {int PageLength; } ;
struct TYPE_18__ {char* BoardName; char* BoardAssembly; char* ChipName; char* ChipRevision; int BiosVersion; int IOCCapabilities; int NumPhys; TYPE_3__* PhyData; TYPE_2__ FWVersion; TYPE_1__ Header; } ;
struct TYPE_17__ {int PortFlags; int PhyFlags; int MaxMinLinkRate; scalar_t__ AttachedDevHandle; int ControllerDevHandle; int NegotiatedLinkRate; int /*<<< orphan*/  ControllerPhyDeviceInfo; } ;
typedef  TYPE_3__ MPI2_SAS_IO_UNIT1_PHY_DATA ;
typedef  TYPE_3__ MPI2_SAS_IO_UNIT0_PHY_DATA ;
typedef  TYPE_5__ MPI2_IOC_FACTS_REPLY ;
typedef  TYPE_5__ MPI2_CONFIG_PAGE_SASIOUNIT_1 ;
typedef  TYPE_5__ MPI2_CONFIG_PAGE_SASIOUNIT_0 ;
typedef  TYPE_5__ MPI2_CONFIG_PAGE_MAN_0 ;
typedef  TYPE_5__ MPI2_CONFIG_PAGE_BIOS_3 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT ; 
 int /*<<< orphan*/  MPI2_CONFIG_PAGETYPE_BIOS ; 
 int MPI2_IOCFACTS_CAPABILITY_INTEGRATED_RAID ; 
 int MPI2_SASIOUNIT0_PHYFLAGS_PHY_DISABLED ; 
 int MPI2_SASIOUNIT0_PORTFLAGS_DISCOVERY_IN_PROGRESS ; 
 int /*<<< orphan*/  MPI2_SASIOUNITPAGE0_PAGEVERSION ; 
 int /*<<< orphan*/  MPI2_SASIOUNITPAGE1_PAGEVERSION ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 char* get_device_speed (int) ; 
 char* get_device_type (int /*<<< orphan*/ ) ; 
 scalar_t__ is_mps ; 
 TYPE_5__* mps_get_iocfacts (int) ; 
 int mps_open (int /*<<< orphan*/ ) ; 
 TYPE_5__* mps_read_config_page (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* mps_read_extended_config_page (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* mps_read_man_page (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mps_unit ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
show_adapter(int ac, char **av)
{
	MPI2_CONFIG_PAGE_SASIOUNIT_0	*sas0;
	MPI2_CONFIG_PAGE_SASIOUNIT_1	*sas1;
	MPI2_SAS_IO_UNIT0_PHY_DATA	*phy0;
	MPI2_SAS_IO_UNIT1_PHY_DATA	*phy1;
	MPI2_CONFIG_PAGE_MAN_0 *man0;
	MPI2_CONFIG_PAGE_BIOS_3 *bios3;
	MPI2_IOC_FACTS_REPLY *facts;
	U16 IOCStatus;
	char *speed, *minspeed, *maxspeed, *isdisabled, *type;
	char devhandle[5], ctrlhandle[5];
	int error, fd, v, i;

	if (ac != 1) {
		warnx("show adapter: extra arguments");
		return (EINVAL);
	}

	fd = mps_open(mps_unit);
	if (fd < 0) {
		error = errno;
		warn("mps_open");
		return (error);
	}

	man0 = mps_read_man_page(fd, 0, NULL);
	if (man0 == NULL) {
		error = errno;
		warn("Failed to get controller info");
		return (error);
	}
	if (man0->Header.PageLength < sizeof(*man0) / 4) {
		warnx("Invalid controller info");
		return (EINVAL);
	}
	printf("mp%s%d Adapter:\n", is_mps ? "s": "r", mps_unit);
	printf("       Board Name: %.16s\n", man0->BoardName);
	printf("   Board Assembly: %.16s\n", man0->BoardAssembly);
	printf("        Chip Name: %.16s\n", man0->ChipName);
	printf("    Chip Revision: %.16s\n", man0->ChipRevision);
	free(man0);

	bios3 = mps_read_config_page(fd, MPI2_CONFIG_PAGETYPE_BIOS, 3, 0, NULL);
	if (bios3 == NULL) {
		error = errno;
		warn("Failed to get BIOS page 3 info");
		return (error);
	}
	v = bios3->BiosVersion;
	printf("    BIOS Revision: %d.%02d.%02d.%02d\n",
	    ((v & 0xff000000) >> 24), ((v &0xff0000) >> 16),
	    ((v & 0xff00) >> 8), (v & 0xff));
	free(bios3);

	if ((facts = mps_get_iocfacts(fd)) == NULL) {
		printf("could not get controller IOCFacts\n");
		close(fd);
		return (errno);
	}
	v = facts->FWVersion.Word;
	printf("Firmware Revision: %d.%02d.%02d.%02d\n",
	    ((v & 0xff000000) >> 24), ((v &0xff0000) >> 16),
	    ((v & 0xff00) >> 8), (v & 0xff));
	printf("  Integrated RAID: %s\n",
	    (facts->IOCCapabilities & MPI2_IOCFACTS_CAPABILITY_INTEGRATED_RAID)
	    ? "yes" : "no");
	free(facts);

	fd = mps_open(mps_unit);
	if (fd < 0) {
		error = errno;
		warn("mps_open");
		return (error);
	}

	sas0 = mps_read_extended_config_page(fd,
	    MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT,
	    MPI2_SASIOUNITPAGE0_PAGEVERSION, 0, 0, &IOCStatus);
	if (sas0 == NULL) {
		error = errno;
		warn("Error retrieving SAS IO Unit page %d", IOCStatus);
		free(sas0);
		close(fd);
		return (error);
	}

	sas1 = mps_read_extended_config_page(fd,
	    MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT,
	    MPI2_SASIOUNITPAGE1_PAGEVERSION, 1, 0, &IOCStatus);
	if (sas1 == NULL) {
		error = errno;
		warn("Error retrieving SAS IO Unit page %d", IOCStatus);
		free(sas0);
		close(fd);
		return (error);
	}
	printf("\n");

	printf("%-8s%-12s%-11s%-10s%-8s%-7s%-7s%s\n", "PhyNum", "CtlrHandle",
	    "DevHandle", "Disabled", "Speed", "Min", "Max", "Device");
	for (i = 0; i < sas0->NumPhys; i++) {
		phy0 = &sas0->PhyData[i];
		phy1 = &sas1->PhyData[i];
		if (phy0->PortFlags &
		     MPI2_SASIOUNIT0_PORTFLAGS_DISCOVERY_IN_PROGRESS) {
			printf("Discovery still in progress\n");
			continue;
		}
		if (phy0->PhyFlags & MPI2_SASIOUNIT0_PHYFLAGS_PHY_DISABLED)
			isdisabled = "Y";
		else
			isdisabled = "N";

		minspeed = get_device_speed(phy1->MaxMinLinkRate);
		maxspeed = get_device_speed(phy1->MaxMinLinkRate >> 4);
		type = get_device_type(phy0->ControllerPhyDeviceInfo);

		if (phy0->AttachedDevHandle != 0) {
			snprintf(devhandle, 5, "%04x", phy0->AttachedDevHandle);
			snprintf(ctrlhandle, 5, "%04x",
			    phy0->ControllerDevHandle);
			speed = get_device_speed(phy0->NegotiatedLinkRate);
		} else {
			snprintf(devhandle, 5, "    ");
			snprintf(ctrlhandle, 5, "    ");
			speed = "     ";
		}
		printf("%-8d%-12s%-11s%-10s%-8s%-7s%-7s%s\n",
		    i, ctrlhandle, devhandle, isdisabled, speed, minspeed,
		    maxspeed, type);
	}
	free(sas0);
	free(sas1);
	printf("\n");
	close(fd);
	return (0);
}