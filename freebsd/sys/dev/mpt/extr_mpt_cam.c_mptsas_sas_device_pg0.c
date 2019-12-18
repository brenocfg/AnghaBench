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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct mptsas_devinfo {int /*<<< orphan*/  device_info; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  bus; int /*<<< orphan*/  target_id; int /*<<< orphan*/  physical_port; int /*<<< orphan*/  phy_num; void* slot; void* enclosure_handle; void* parent_dev_handle; void* dev_handle; } ;
struct mpt_softc {int dummy; } ;
struct TYPE_9__ {scalar_t__ ExtPageLength; } ;
struct TYPE_8__ {int /*<<< orphan*/  DeviceInfo; int /*<<< orphan*/  SASAddress; int /*<<< orphan*/  Bus; int /*<<< orphan*/  TargetID; int /*<<< orphan*/  PhysicalPort; int /*<<< orphan*/  PhyNum; int /*<<< orphan*/  Slot; int /*<<< orphan*/  EnclosureHandle; int /*<<< orphan*/  ParentDevHandle; int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_1__ SasDevicePage0_t ;
typedef  TYPE_2__ ConfigExtendedPageHeader_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_EXTPAGETYPE_SAS_DEVICE ; 
 int /*<<< orphan*/  MPI_SASDEVICE0_PAGEVERSION ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct mptsas_devinfo*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mpt_read_extcfg_header (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int mpt_read_extcfg_page (struct mpt_softc*,int /*<<< orphan*/ ,scalar_t__,TYPE_2__*,TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mptsas_sas_device_pg0(struct mpt_softc *mpt, struct mptsas_devinfo *device_info,
	uint32_t form, uint32_t form_specific)
{
	ConfigExtendedPageHeader_t hdr;
	SasDevicePage0_t *buffer;
	uint64_t sas_address;
	int error = 0;

	bzero(device_info, sizeof(*device_info));
	error = mpt_read_extcfg_header(mpt, MPI_SASDEVICE0_PAGEVERSION, 0, 0,
				       MPI_CONFIG_EXTPAGETYPE_SAS_DEVICE,
				       &hdr, 0, 10000);
	if (error)
		goto out;
	if (hdr.ExtPageLength == 0) {
		error = ENXIO;
		goto out;
	}

	buffer = malloc(sizeof(SasDevicePage0_t), M_DEVBUF, M_NOWAIT|M_ZERO);
	if (buffer == NULL) {
		error = ENOMEM;
		goto out;
	}

	error = mpt_read_extcfg_page(mpt, MPI_CONFIG_ACTION_PAGE_READ_CURRENT,
				     form + form_specific, &hdr, buffer,
				     sizeof(SasDevicePage0_t), 0, 10000);
	if (error) {
		free(buffer, M_DEVBUF);
		goto out;
	}

	device_info->dev_handle = le16toh(buffer->DevHandle);
	device_info->parent_dev_handle = le16toh(buffer->ParentDevHandle);
	device_info->enclosure_handle = le16toh(buffer->EnclosureHandle);
	device_info->slot = le16toh(buffer->Slot);
	device_info->phy_num = buffer->PhyNum;
	device_info->physical_port = buffer->PhysicalPort;
	device_info->target_id = buffer->TargetID;
	device_info->bus = buffer->Bus;
	bcopy(&buffer->SASAddress, &sas_address, sizeof(uint64_t));
	device_info->sas_address = le64toh(sas_address);
	device_info->device_info = le32toh(buffer->DeviceInfo);

	free(buffer, M_DEVBUF);
out:
	return (error);
}