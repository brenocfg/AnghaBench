#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct iwm_softc {TYPE_2__* nvm_data; int /*<<< orphan*/  sc_dev; TYPE_1__* cfg; } ;
struct iwm_nvm_section {int /*<<< orphan*/ * data; scalar_t__ length; } ;
typedef  int /*<<< orphan*/  nvm_sections ;
struct TYPE_4__ {int /*<<< orphan*/  nvm_version; } ;
struct TYPE_3__ {int nvm_hw_section_num; scalar_t__ eeprom_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int IWM_DEBUG_EEPROM ; 
 int IWM_DEBUG_RESET ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int,char*,...) ; 
 int IWM_NVM_MAX_NUM_SECTIONS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwm_nvm_read_section (struct iwm_softc*,int,int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 TYPE_2__* iwm_parse_nvm_sections (struct iwm_softc*,struct iwm_nvm_section*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct iwm_nvm_section*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwm_nvm_init(struct iwm_softc *sc)
{
	struct iwm_nvm_section nvm_sections[IWM_NVM_MAX_NUM_SECTIONS];
	int i, ret, section;
	uint32_t size_read = 0;
	uint8_t *nvm_buffer, *temp;
	uint16_t len;

	memset(nvm_sections, 0, sizeof(nvm_sections));

	if (sc->cfg->nvm_hw_section_num >= IWM_NVM_MAX_NUM_SECTIONS)
		return EINVAL;

	/* load NVM values from nic */
	/* Read From FW NVM */
	IWM_DPRINTF(sc, IWM_DEBUG_EEPROM, "Read from NVM\n");

	nvm_buffer = malloc(sc->cfg->eeprom_size, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (!nvm_buffer)
		return ENOMEM;
	for (section = 0; section < IWM_NVM_MAX_NUM_SECTIONS; section++) {
		/* we override the constness for initial read */
		ret = iwm_nvm_read_section(sc, section, nvm_buffer,
					   &len, size_read);
		if (ret)
			continue;
		size_read += len;
		temp = malloc(len, M_DEVBUF, M_NOWAIT);
		if (!temp) {
			ret = ENOMEM;
			break;
		}
		memcpy(temp, nvm_buffer, len);

		nvm_sections[section].data = temp;
		nvm_sections[section].length = len;
	}
	if (!size_read)
		device_printf(sc->sc_dev, "OTP is blank\n");
	free(nvm_buffer, M_DEVBUF);

	sc->nvm_data = iwm_parse_nvm_sections(sc, nvm_sections);
	if (!sc->nvm_data)
		return EINVAL;
	IWM_DPRINTF(sc, IWM_DEBUG_EEPROM | IWM_DEBUG_RESET,
		    "nvm version = %x\n", sc->nvm_data->nvm_version);

	for (i = 0; i < IWM_NVM_MAX_NUM_SECTIONS; i++) {
		if (nvm_sections[i].data != NULL)
			free(nvm_sections[i].data, M_DEVBUF);
	}

	return 0;
}