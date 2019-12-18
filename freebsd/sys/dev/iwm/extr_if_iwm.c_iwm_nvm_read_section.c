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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ eeprom_size; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int IWM_DEBUG_EEPROM ; 
 int IWM_DEBUG_RESET ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int,char*,scalar_t__,...) ; 
 scalar_t__ IWM_NVM_DEFAULT_CHUNK_SIZE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int iwm_nvm_read_chunk (struct iwm_softc*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int
iwm_nvm_read_section(struct iwm_softc *sc,
	uint16_t section, uint8_t *data, uint16_t *len, uint32_t size_read)
{
	uint16_t seglen, length, offset = 0;
	int ret;

	/* Set nvm section read length */
	length = IWM_NVM_DEFAULT_CHUNK_SIZE;

	seglen = length;

	/* Read the NVM until exhausted (reading less than requested) */
	while (seglen == length) {
		/* Check no memory assumptions fail and cause an overflow */
		if ((size_read + offset + length) >
		    sc->cfg->eeprom_size) {
			device_printf(sc->sc_dev,
			    "EEPROM size is too small for NVM\n");
			return ENOBUFS;
		}

		ret = iwm_nvm_read_chunk(sc, section, offset, length, data, &seglen);
		if (ret) {
			IWM_DPRINTF(sc, IWM_DEBUG_EEPROM | IWM_DEBUG_RESET,
				    "Cannot read NVM from section %d offset %d, length %d\n",
				    section, offset, length);
			return ret;
		}
		offset += seglen;
	}

	IWM_DPRINTF(sc, IWM_DEBUG_EEPROM | IWM_DEBUG_RESET,
		    "NVM section %d read completed\n", section);
	*len = offset;
	return 0;
}