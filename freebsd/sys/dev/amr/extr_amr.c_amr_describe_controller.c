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
struct amr_softc {int /*<<< orphan*/  amr_dev; } ;
struct TYPE_2__ {char* aa_firmware; char* aa_bios; int /*<<< orphan*/  aa_memorysize; } ;
struct amr_prodinfo {char* ap_product; char* ap_firmware; char* ap_bios; scalar_t__ ae_signature; TYPE_1__ ae_adapter; int /*<<< orphan*/  ap_memsize; } ;
struct amr_enquiry {char* ap_product; char* ap_firmware; char* ap_bios; scalar_t__ ae_signature; TYPE_1__ ae_adapter; int /*<<< orphan*/  ap_memsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMR_CMD_CONFIG ; 
 int /*<<< orphan*/  AMR_CMD_ENQUIRY ; 
 int /*<<< orphan*/  AMR_CMD_EXT_ENQUIRY2 ; 
 int /*<<< orphan*/  AMR_CONFIG_PRODUCT_INFO ; 
 scalar_t__ AMR_SIG_438 ; 
 int /*<<< orphan*/  M_AMR ; 
 char* amr_describe_code (int /*<<< orphan*/ ,scalar_t__) ; 
 struct amr_prodinfo* amr_enquiry (struct amr_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  amr_table_adaptertype ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct amr_prodinfo*,int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amr_describe_controller(struct amr_softc *sc)
{
    struct amr_prodinfo	*ap;
    struct amr_enquiry	*ae;
    char		*prod;
    int			status;

    /*
     * Try to get 40LD product info, which tells us what the card is labelled as.
     */
    if ((ap = amr_enquiry(sc, 2048, AMR_CMD_CONFIG, AMR_CONFIG_PRODUCT_INFO, 0, &status)) != NULL) {
	device_printf(sc->amr_dev, "<LSILogic %.80s> Firmware %.16s, BIOS %.16s, %dMB RAM\n",
		      ap->ap_product, ap->ap_firmware, ap->ap_bios,
		      ap->ap_memsize);

	free(ap, M_AMR);
	return;
    }

    /*
     * Try 8LD extended ENQUIRY to get controller signature, and use lookup table.
     */
    if ((ae = (struct amr_enquiry *)amr_enquiry(sc, 2048, AMR_CMD_EXT_ENQUIRY2, 0, 0, &status)) != NULL) {
	prod = amr_describe_code(amr_table_adaptertype, ae->ae_signature);

    } else if ((ae = (struct amr_enquiry *)amr_enquiry(sc, 2048, AMR_CMD_ENQUIRY, 0, 0, &status)) != NULL) {

	/*
	 * Try to work it out based on the PCI signatures.
	 */
	switch (pci_get_device(sc->amr_dev)) {
	case 0x9010:
	    prod = "Series 428";
	    break;
	case 0x9060:
	    prod = "Series 434";
	    break;
	default:
	    prod = "unknown controller";
	    break;
	}
    } else {
	device_printf(sc->amr_dev, "<unsupported controller>\n");
	return;
    }

    /*
     * HP NetRaid controllers have a special encoding of the firmware and
     * BIOS versions. The AMI version seems to have it as strings whereas
     * the HP version does it with a leading uppercase character and two
     * binary numbers.
     */
     
    if(ae->ae_adapter.aa_firmware[2] >= 'A' &&
       ae->ae_adapter.aa_firmware[2] <= 'Z' &&
       ae->ae_adapter.aa_firmware[1] <  ' ' &&
       ae->ae_adapter.aa_firmware[0] <  ' ' &&
       ae->ae_adapter.aa_bios[2] >= 'A'     &&
       ae->ae_adapter.aa_bios[2] <= 'Z'     &&
       ae->ae_adapter.aa_bios[1] <  ' '     &&
       ae->ae_adapter.aa_bios[0] <  ' ') {

	/* this looks like we have an HP NetRaid version of the MegaRaid */

    	if(ae->ae_signature == AMR_SIG_438) {
    		/* the AMI 438 is a NetRaid 3si in HP-land */
    		prod = "HP NetRaid 3si";
    	}
    	
	device_printf(sc->amr_dev, "<%s> Firmware %c.%02d.%02d, BIOS %c.%02d.%02d, %dMB RAM\n",
		      prod, ae->ae_adapter.aa_firmware[2],
		      ae->ae_adapter.aa_firmware[1],
		      ae->ae_adapter.aa_firmware[0],
		      ae->ae_adapter.aa_bios[2],
		      ae->ae_adapter.aa_bios[1],
		      ae->ae_adapter.aa_bios[0],
		      ae->ae_adapter.aa_memorysize);		
    } else {
	device_printf(sc->amr_dev, "<%s> Firmware %.4s, BIOS %.4s, %dMB RAM\n", 
		      prod, ae->ae_adapter.aa_firmware, ae->ae_adapter.aa_bios,
		      ae->ae_adapter.aa_memorysize);
    }    	
    free(ae, M_AMR);
}