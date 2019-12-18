#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int16_t ;
struct volume_tag {int dummy; } ;
struct read_element_status_device_id {size_t designator_length; int piv_assoc_designator_type; int /*<<< orphan*/  prot_code_set; scalar_t__ designator; } ;
struct TYPE_9__ {int dt_scsi_flags; int dt_scsi_addr; } ;
struct TYPE_10__ {TYPE_4__ scsi_2; } ;
struct TYPE_7__ {struct read_element_status_device_id devid; } ;
struct TYPE_6__ {struct read_element_status_device_id devid; } ;
struct TYPE_8__ {TYPE_2__ vol_tags_and_devid; struct read_element_status_device_id devid; TYPE_1__ pvol_and_devid; struct volume_tag pvoltag; struct volume_tag* voltag; } ;
struct read_element_status_descriptor {int flags1; int flags2; TYPE_5__ dt_or_obsolete; TYPE_3__ voltag_devid; int /*<<< orphan*/  ssea; int /*<<< orphan*/  sense_qual; int /*<<< orphan*/  sense_code; int /*<<< orphan*/  eaddr; } ;
struct changer_element_status {size_t ces_int_addr; size_t ces_addr; size_t ces_type; int ces_flags; size_t ces_source_addr; size_t ces_source_type; char* ces_designator; size_t ces_designator_length; int ces_scsi_id; int ces_scsi_lun; int /*<<< orphan*/  ces_protocol_id; int /*<<< orphan*/  ces_designator_type; int /*<<< orphan*/  ces_assoc; int /*<<< orphan*/  ces_code_set; int /*<<< orphan*/  ces_pvoltag; int /*<<< orphan*/  ces_sensequal; int /*<<< orphan*/  ces_sensecode; } ;
struct ch_softc {size_t* sc_firsts; size_t* sc_counts; } ;

/* Variables and functions */
 int CES_INVERT ; 
 int CES_LUN_VALID ; 
 int CES_PIV ; 
 int /*<<< orphan*/  CES_PROTOCOL_ID_FCP_4 ; 
 int CES_SCSIID_VALID ; 
 int CES_SOURCE_VALID ; 
 size_t CHET_DT ; 
 size_t CHET_MT ; 
 int /*<<< orphan*/  READ_ELEMENT_STATUS_ASSOCIATION (int) ; 
 size_t READ_ELEMENT_STATUS_AVOLTAG ; 
 int /*<<< orphan*/  READ_ELEMENT_STATUS_CODE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ELEMENT_STATUS_DESIGNATOR_TYPE (int) ; 
 int READ_ELEMENT_STATUS_DT_IDVALID ; 
 int READ_ELEMENT_STATUS_DT_LUNMASK ; 
 int READ_ELEMENT_STATUS_DT_LUVALID ; 
 int READ_ELEMENT_STATUS_INVERT ; 
 int READ_ELEMENT_STATUS_PIV_SET ; 
 int /*<<< orphan*/  READ_ELEMENT_STATUS_PROTOCOL_ID (int /*<<< orphan*/ ) ; 
 size_t READ_ELEMENT_STATUS_PVOLTAG ; 
 int READ_ELEMENT_STATUS_SVALID ; 
 int SCSI_REV_2 ; 
 int SCSI_REV_SPC ; 
 int /*<<< orphan*/  bcopy (void*,void*,size_t) ; 
 int /*<<< orphan*/  copy_voltag (int /*<<< orphan*/ *,struct volume_tag*) ; 
 int /*<<< orphan*/  printf (char*,size_t) ; 
 size_t scsi_2btoul (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
copy_element_status(struct ch_softc *softc,
		    u_int16_t flags,
		    struct read_element_status_descriptor *desc,
		    struct changer_element_status *ces,
		    int scsi_version)
{
	u_int16_t eaddr = scsi_2btoul(desc->eaddr);
	u_int16_t et;
	struct volume_tag *pvol_tag = NULL, *avol_tag = NULL;
	struct read_element_status_device_id *devid = NULL;

	ces->ces_int_addr = eaddr;
	/* set up logical address in element status */
	for (et = CHET_MT; et <= CHET_DT; et++) {
		if ((softc->sc_firsts[et] <= eaddr)
		    && ((softc->sc_firsts[et] + softc->sc_counts[et])
			> eaddr)) {
			ces->ces_addr = eaddr - softc->sc_firsts[et];
			ces->ces_type = et;
			break;
		}
	}

	ces->ces_flags = desc->flags1;

	ces->ces_sensecode = desc->sense_code;
	ces->ces_sensequal = desc->sense_qual;

	if (desc->flags2 & READ_ELEMENT_STATUS_INVERT)
		ces->ces_flags |= CES_INVERT;

	if (desc->flags2 & READ_ELEMENT_STATUS_SVALID) {

		eaddr = scsi_2btoul(desc->ssea);

		/* convert source address to logical format */
		for (et = CHET_MT; et <= CHET_DT; et++) {
			if ((softc->sc_firsts[et] <= eaddr)
			    && ((softc->sc_firsts[et] + softc->sc_counts[et])
				> eaddr)) {
				ces->ces_source_addr =
					eaddr - softc->sc_firsts[et];
				ces->ces_source_type = et;
				ces->ces_flags |= CES_SOURCE_VALID;
				break;
			}
		}

		if (!(ces->ces_flags & CES_SOURCE_VALID))
			printf("ch: warning: could not map element source "
			       "address %ud to a valid element type\n",
			       eaddr);
	}

	/*
	 * pvoltag and avoltag are common between SCSI-2 and later versions
	 */
	if (flags & READ_ELEMENT_STATUS_PVOLTAG)
		pvol_tag = &desc->voltag_devid.pvoltag;
	if (flags & READ_ELEMENT_STATUS_AVOLTAG)
		avol_tag = (flags & READ_ELEMENT_STATUS_PVOLTAG) ?
		    &desc->voltag_devid.voltag[1] :&desc->voltag_devid.pvoltag;
	/*
	 * For SCSI-3 and later, element status can carry designator and
	 * other information.
	 */
	if (scsi_version >= SCSI_REV_SPC) {
		if ((flags & READ_ELEMENT_STATUS_PVOLTAG) ^
		    (flags & READ_ELEMENT_STATUS_AVOLTAG))
			devid = &desc->voltag_devid.pvol_and_devid.devid;
		else if (!(flags & READ_ELEMENT_STATUS_PVOLTAG) &&
			 !(flags & READ_ELEMENT_STATUS_AVOLTAG))
			devid = &desc->voltag_devid.devid;
		else /* Have both PVOLTAG and AVOLTAG */
			devid = &desc->voltag_devid.vol_tags_and_devid.devid;
	}

	if (pvol_tag)
		copy_voltag(&(ces->ces_pvoltag), pvol_tag);
	if (avol_tag)
		copy_voltag(&(ces->ces_pvoltag), avol_tag);
	if (devid != NULL) {
		if (devid->designator_length > 0) {
			bcopy((void *)devid->designator,
			      (void *)ces->ces_designator,
			      devid->designator_length);
			ces->ces_designator_length = devid->designator_length;
			/*
			 * Make sure we are always NUL terminated.  The
			 * This won't matter for the binary code set,
			 * since the user will only pay attention to the
			 * length field.
			 */
			ces->ces_designator[devid->designator_length]= '\0';
		}
		if (devid->piv_assoc_designator_type &
		    READ_ELEMENT_STATUS_PIV_SET) {
			ces->ces_flags |= CES_PIV;
			ces->ces_protocol_id =
			    READ_ELEMENT_STATUS_PROTOCOL_ID(
			    devid->prot_code_set);
		}
		ces->ces_code_set =
		    READ_ELEMENT_STATUS_CODE_SET(devid->prot_code_set);
		ces->ces_assoc = READ_ELEMENT_STATUS_ASSOCIATION(
		    devid->piv_assoc_designator_type);
		ces->ces_designator_type = READ_ELEMENT_STATUS_DESIGNATOR_TYPE(
		    devid->piv_assoc_designator_type);
	} else if (scsi_version > SCSI_REV_2) {
		/* SCSI-SPC and No devid, no designator */
		ces->ces_designator_length = 0;
		ces->ces_designator[0] = '\0';
		ces->ces_protocol_id = CES_PROTOCOL_ID_FCP_4;
	}

	if (scsi_version <= SCSI_REV_2) {
		if (desc->dt_or_obsolete.scsi_2.dt_scsi_flags &
		    READ_ELEMENT_STATUS_DT_IDVALID) {
			ces->ces_flags |= CES_SCSIID_VALID;
			ces->ces_scsi_id =
			    desc->dt_or_obsolete.scsi_2.dt_scsi_addr;
		}

		if (desc->dt_or_obsolete.scsi_2.dt_scsi_addr &
		    READ_ELEMENT_STATUS_DT_LUVALID) {
			ces->ces_flags |= CES_LUN_VALID;
			ces->ces_scsi_lun =
			    desc->dt_or_obsolete.scsi_2.dt_scsi_flags &
			    READ_ELEMENT_STATUS_DT_LUNMASK;
		}
	}
}