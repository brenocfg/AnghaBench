#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct scsi_transportid_spi {int format_protocol; int /*<<< orphan*/  rel_trgt_port_id; int /*<<< orphan*/  scsi_addr; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  additional_length; int /*<<< orphan*/  iscsi_name; int /*<<< orphan*/  n_port_name; } ;
struct scsi_transportid_sas {int format_protocol; int /*<<< orphan*/  rel_trgt_port_id; int /*<<< orphan*/  scsi_addr; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  additional_length; int /*<<< orphan*/  iscsi_name; int /*<<< orphan*/  n_port_name; } ;
struct scsi_transportid_iscsi_port {int format_protocol; int /*<<< orphan*/  rel_trgt_port_id; int /*<<< orphan*/  scsi_addr; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  additional_length; int /*<<< orphan*/  iscsi_name; int /*<<< orphan*/  n_port_name; } ;
struct scsi_transportid_fcp {int format_protocol; int /*<<< orphan*/  rel_trgt_port_id; int /*<<< orphan*/  scsi_addr; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  additional_length; int /*<<< orphan*/  iscsi_name; int /*<<< orphan*/  n_port_name; } ;
struct ctl_port {int port_type; int targ_port; TYPE_1__* wwpn_iid; } ;
struct TYPE_2__ {int /*<<< orphan*/  wwpn; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
#define  CTL_PORT_FC 130 
#define  CTL_PORT_ISCSI 129 
#define  CTL_PORT_SAS 128 
 int SCSI_PROTO_FC ; 
 int SCSI_PROTO_ISCSI ; 
 int SCSI_PROTO_SAS ; 
 int SCSI_PROTO_SPI ; 
 int SCSI_TRN_ISCSI_FORMAT_PORT ; 
 int /*<<< orphan*/  memset (struct scsi_transportid_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int roundup2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_u64to8b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ctl_create_iid(struct ctl_port *port, int iid, uint8_t *buf)
{
	int len;

	switch (port->port_type) {
	case CTL_PORT_FC:
	{
		struct scsi_transportid_fcp *id =
		    (struct scsi_transportid_fcp *)buf;
		if (port->wwpn_iid[iid].wwpn == 0)
			return (0);
		memset(id, 0, sizeof(*id));
		id->format_protocol = SCSI_PROTO_FC;
		scsi_u64to8b(port->wwpn_iid[iid].wwpn, id->n_port_name);
		return (sizeof(*id));
	}
	case CTL_PORT_ISCSI:
	{
		struct scsi_transportid_iscsi_port *id =
		    (struct scsi_transportid_iscsi_port *)buf;
		if (port->wwpn_iid[iid].name == NULL)
			return (0);
		memset(id, 0, 256);
		id->format_protocol = SCSI_TRN_ISCSI_FORMAT_PORT |
		    SCSI_PROTO_ISCSI;
		len = strlcpy(id->iscsi_name, port->wwpn_iid[iid].name, 252) + 1;
		len = roundup2(min(len, 252), 4);
		scsi_ulto2b(len, id->additional_length);
		return (sizeof(*id) + len);
	}
	case CTL_PORT_SAS:
	{
		struct scsi_transportid_sas *id =
		    (struct scsi_transportid_sas *)buf;
		if (port->wwpn_iid[iid].wwpn == 0)
			return (0);
		memset(id, 0, sizeof(*id));
		id->format_protocol = SCSI_PROTO_SAS;
		scsi_u64to8b(port->wwpn_iid[iid].wwpn, id->sas_address);
		return (sizeof(*id));
	}
	default:
	{
		struct scsi_transportid_spi *id =
		    (struct scsi_transportid_spi *)buf;
		memset(id, 0, sizeof(*id));
		id->format_protocol = SCSI_PROTO_SPI;
		scsi_ulto2b(iid, id->scsi_addr);
		scsi_ulto2b(port->targ_port, id->rel_trgt_port_id);
		return (sizeof(*id));
	}
	}
}