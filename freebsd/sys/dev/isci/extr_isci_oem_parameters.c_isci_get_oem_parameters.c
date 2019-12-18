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
typedef  char uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct rom_header {int pcir_pointer; } ;
struct pcir_header {scalar_t__ vendor_id; scalar_t__ device_id; } ;
struct oem_parameters_table {scalar_t__ data; } ;
struct TYPE_6__ {scalar_t__ vendor_id; scalar_t__ device_id; } ;
struct isci_softc {TYPE_3__* controllers; int /*<<< orphan*/  oem_parameters_found; TYPE_1__ pci_common_header; } ;
struct TYPE_9__ {int num_elements; int /*<<< orphan*/  version; } ;
struct TYPE_10__ {TYPE_4__ header; int /*<<< orphan*/ * controller_element; } ;
struct TYPE_7__ {int /*<<< orphan*/  sds1; } ;
struct TYPE_8__ {int /*<<< orphan*/  oem_parameters_version; TYPE_2__ oem_parameters; } ;
typedef  TYPE_5__ SCI_BIOS_OEM_PARAM_BLOCK_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_OEM_PARAMETERS_T ;

/* Variables and functions */
 scalar_t__ BIOS_PADDRTOVADDR (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  isci_log_message (int,char*,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
isci_get_oem_parameters(struct isci_softc *isci)
{
	uint32_t OROM_PHYSICAL_ADDRESS_START = 0xC0000;
	uint32_t OROM_SEARCH_LENGTH = 0x30000;
	uint16_t OROM_SIGNATURE = 0xAA55;
	uint32_t OROM_SIZE = 512;
	uint8_t *orom_start =
	    (uint8_t *)BIOS_PADDRTOVADDR(OROM_PHYSICAL_ADDRESS_START);
	uint32_t offset = 0;

	while (offset < OROM_SEARCH_LENGTH) {

		/* Look for the OROM signature at the beginning of every
		 *  512-byte block in the OROM region
		 */
		if (*(uint16_t*)(orom_start + offset) == OROM_SIGNATURE) {
			uint32_t *rom;
			struct rom_header *rom_header;
			struct pcir_header *pcir_header;
			uint16_t vendor_id = isci->pci_common_header.vendor_id;
			uint16_t device_id = isci->pci_common_header.device_id;

			rom = (uint32_t *)(orom_start + offset);
			rom_header = (struct rom_header *)rom;
			pcir_header = (struct pcir_header *)
			    ((uint8_t*)rom + rom_header->pcir_pointer);

			/* OROM signature was found.  Now check if the PCI
			 *  device and vendor IDs match.
			 */
			if (pcir_header->vendor_id == vendor_id &&
			    pcir_header->device_id == device_id)
			{
				/* OROM for this PCI device was found.  Search
				 *  this 512-byte block for the $OEM string,
				 *  which will mark the beginning of the OEM
				 *  parameter block.
				 */
				uint8_t oem_sig[4] = {'$', 'O', 'E', 'M'};
				int dword_index;

				for (dword_index = 0;
				    dword_index < OROM_SIZE/sizeof(uint32_t);
				    dword_index++)
					if (rom[dword_index] == *(uint32_t *)oem_sig) {
						/* $OEM signature string was found.  Now copy the OEM parameter block
						 *  into the struct ISCI_CONTROLLER objects.  After the controllers are
						 *  constructed, we will pass this OEM parameter data to the SCI core
						 *  controller.
						 */
						struct oem_parameters_table *oem =
							(struct oem_parameters_table *)&rom[dword_index];
						SCI_BIOS_OEM_PARAM_BLOCK_T *oem_data =
							(SCI_BIOS_OEM_PARAM_BLOCK_T *)oem->data;
						int index;

						isci->oem_parameters_found = TRUE;
						isci_log_message(1, "ISCI", "oem_data->header.num_elements = %d\n",
						    oem_data->header.num_elements);

						for (index = 0; index < oem_data->header.num_elements; index++)
						{
							memcpy(&isci->controllers[index].oem_parameters.sds1,
							       &oem_data->controller_element[index],
							       sizeof(SCIC_SDS_OEM_PARAMETERS_T));

							isci_log_message(1, "ISCI", "OEM Parameter Data for controller %d\n",
							    index);

							for (int i = 0; i < sizeof(SCIC_SDS_OEM_PARAMETERS_T); i++) {
								uint8_t val = ((uint8_t *)&oem_data->controller_element[index])[i];
								isci_log_message(1, "ISCI", "%02x ", val);
							}
							isci_log_message(1, "ISCI", "\n");
							isci->controllers[index].oem_parameters_version = oem_data->header.version;
						}
					}

				/* No need to continue searching for another
				 *  OROM that matches this PCI device, so return
				 *  immediately.
				 */
				return;
			}
		}

		offset += OROM_SIZE;
	}
}