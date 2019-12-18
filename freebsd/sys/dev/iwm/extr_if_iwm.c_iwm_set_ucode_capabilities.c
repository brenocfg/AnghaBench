#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint32_t ;
struct iwm_ucode_capabilities {int /*<<< orphan*/  enabled_capa; } ;
struct iwm_ucode_capa {int /*<<< orphan*/  api_capa; int /*<<< orphan*/  api_index; } ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_NUM_UCODE_TLV_CAPA ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int howmany (int /*<<< orphan*/ ,int) ; 
 unsigned int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwm_set_ucode_capabilities(struct iwm_softc *sc, const uint8_t *data,
			   struct iwm_ucode_capabilities *capa)
{
	const struct iwm_ucode_capa *ucode_capa = (const void *)data;
	uint32_t api_index = le32toh(ucode_capa->api_index);
	uint32_t api_flags = le32toh(ucode_capa->api_capa);
	int i;

	if (api_index >= howmany(IWM_NUM_UCODE_TLV_CAPA, 32)) {
		device_printf(sc->sc_dev,
		    "capa flags index %d larger than supported by driver\n",
		    api_index);
		/* don't return an error so we can load FW that has more bits */
		return 0;
	}

	for (i = 0; i < 32; i++) {
		if (api_flags & (1U << i))
			setbit(capa->enabled_capa, i + 32 * api_index);
	}

	return 0;
}