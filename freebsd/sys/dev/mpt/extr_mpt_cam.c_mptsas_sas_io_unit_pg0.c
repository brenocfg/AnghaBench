#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mptsas_portinfo {int num_phys; struct mptsas_phyinfo* phy_info; } ;
struct mptsas_phyinfo {int phy_num; int /*<<< orphan*/  handle; int /*<<< orphan*/  negotiated_link_rate; int /*<<< orphan*/  port_id; } ;
struct mpt_softc {int dummy; } ;
struct TYPE_10__ {int ExtPageLength; } ;
struct TYPE_9__ {int NumPhys; TYPE_1__* PhyData; } ;
struct TYPE_8__ {int /*<<< orphan*/  ControllerDevHandle; int /*<<< orphan*/  NegotiatedLinkRate; int /*<<< orphan*/  Port; } ;
typedef  TYPE_2__ SasIOUnitPage0_t ;
typedef  TYPE_3__ ConfigExtendedPageHeader_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT ; 
 int /*<<< orphan*/  MPI_SASIOUNITPAGE0_PAGEVERSION ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mpt_read_extcfg_header (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int mpt_read_extcfg_page (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mptsas_sas_io_unit_pg0(struct mpt_softc *mpt, struct mptsas_portinfo *portinfo)
{
	ConfigExtendedPageHeader_t hdr;
	struct mptsas_phyinfo *phyinfo;
	SasIOUnitPage0_t *buffer;
	int error, len, i;

	error = mpt_read_extcfg_header(mpt, MPI_SASIOUNITPAGE0_PAGEVERSION,
				       0, 0, MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT,
				       &hdr, 0, 10000);
	if (error)
		goto out;
	if (hdr.ExtPageLength == 0) {
		error = ENXIO;
		goto out;
	}

	len = hdr.ExtPageLength * 4;
	buffer = malloc(len, M_DEVBUF, M_NOWAIT|M_ZERO);
	if (buffer == NULL) {
		error = ENOMEM;
		goto out;
	}

	error = mpt_read_extcfg_page(mpt, MPI_CONFIG_ACTION_PAGE_READ_CURRENT,
				     0, &hdr, buffer, len, 0, 10000);
	if (error) {
		free(buffer, M_DEVBUF);
		goto out;
	}

	portinfo->num_phys = buffer->NumPhys;
	portinfo->phy_info = malloc(sizeof(*portinfo->phy_info) *
	    portinfo->num_phys, M_DEVBUF, M_NOWAIT|M_ZERO);
	if (portinfo->phy_info == NULL) {
		free(buffer, M_DEVBUF);
		error = ENOMEM;
		goto out;
	}

	for (i = 0; i < portinfo->num_phys; i++) {
		phyinfo = &portinfo->phy_info[i];
		phyinfo->phy_num = i;
		phyinfo->port_id = buffer->PhyData[i].Port;
		phyinfo->negotiated_link_rate =
		    buffer->PhyData[i].NegotiatedLinkRate;
		phyinfo->handle =
		    le16toh(buffer->PhyData[i].ControllerDevHandle);
	}

	free(buffer, M_DEVBUF);
out:
	return (error);
}