#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pqisrc_softstate {int dummy; } ;
struct ccb_trans_settings_spi {int /*<<< orphan*/  flags; int /*<<< orphan*/  valid; } ;
struct ccb_trans_settings_scsi {int /*<<< orphan*/  flags; int /*<<< orphan*/  valid; } ;
struct ccb_trans_settings_sas {int /*<<< orphan*/  valid; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {struct ccb_trans_settings_spi spi; struct ccb_trans_settings_sas sas; } ;
struct TYPE_4__ {struct ccb_trans_settings_scsi scsi; } ;
struct ccb_trans_settings {int transport_version; TYPE_3__ ccb_h; int /*<<< orphan*/  transport; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; TYPE_2__ xport_specific; TYPE_1__ proto_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CTS_SAS_VALID_SPEED ; 
 int /*<<< orphan*/  CTS_SCSI_FLAGS_TAG_ENB ; 
 int /*<<< orphan*/  CTS_SCSI_VALID_TQ ; 
 int /*<<< orphan*/  CTS_SPI_FLAGS_DISC_ENB ; 
 int /*<<< orphan*/  CTS_SPI_VALID_DISC ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  PROTO_SCSI ; 
 int /*<<< orphan*/  SCSI_REV_SPC4 ; 
 int /*<<< orphan*/  XPORT_SPI ; 

__attribute__((used)) static void get_transport_settings(struct pqisrc_softstate *softs,
		struct ccb_trans_settings *cts)
{
	struct ccb_trans_settings_scsi	*scsi = &cts->proto_specific.scsi;
	struct ccb_trans_settings_sas	*sas = &cts->xport_specific.sas;
	struct ccb_trans_settings_spi	*spi = &cts->xport_specific.spi;

	DBG_FUNC("IN\n");
	
	cts->protocol = PROTO_SCSI;
	cts->protocol_version = SCSI_REV_SPC4;
	cts->transport = XPORT_SPI;
	cts->transport_version = 2;
	spi->valid = CTS_SPI_VALID_DISC;
	spi->flags = CTS_SPI_FLAGS_DISC_ENB;
	scsi->valid = CTS_SCSI_VALID_TQ;
	scsi->flags = CTS_SCSI_FLAGS_TAG_ENB;
	sas->valid = CTS_SAS_VALID_SPEED;
	cts->ccb_h.status = CAM_REQ_CMP;

	DBG_FUNC("OUT\n");
}