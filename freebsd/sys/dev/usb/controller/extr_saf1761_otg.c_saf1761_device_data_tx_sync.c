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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct saf1761_otg_td {int ep_index; } ;
struct saf1761_otg_softc {int sc_dv_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int SAF1761_READ_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAF1761_WRITE_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOTG_BUF_LENGTH ; 
 int SOTG_BUF_LENGTH_FILLED_MASK ; 
 int /*<<< orphan*/  SOTG_EP_INDEX ; 
 int SOTG_EP_INDEX_DIR_IN ; 
 int SOTG_EP_INDEX_ENDP_INDEX_SHIFT ; 
 int SOTG_EP_INDEX_EP0SETUP ; 
 int /*<<< orphan*/  saf1761_otg_set_address (struct saf1761_otg_softc*,int) ; 

__attribute__((used)) static uint8_t
saf1761_device_data_tx_sync(struct saf1761_otg_softc *sc, struct saf1761_otg_td *td)
{
	uint32_t count;

	if (td->ep_index == 0) {
		/* select the correct endpoint */
		SAF1761_WRITE_LE_4(sc, SOTG_EP_INDEX, SOTG_EP_INDEX_EP0SETUP);

		count = SAF1761_READ_LE_4(sc, SOTG_BUF_LENGTH);

		/* check buffer status */
		if ((count & SOTG_BUF_LENGTH_FILLED_MASK) != 0) {
			DPRINTFN(5, "Faking complete\n");
			return (0);	/* complete */
		}
	}
	/* select the correct endpoint */
	SAF1761_WRITE_LE_4(sc, SOTG_EP_INDEX,
	    (td->ep_index << SOTG_EP_INDEX_ENDP_INDEX_SHIFT) |
	    SOTG_EP_INDEX_DIR_IN);

	count = SAF1761_READ_LE_4(sc, SOTG_BUF_LENGTH);

	/* check buffer status */
	if ((count & SOTG_BUF_LENGTH_FILLED_MASK) != 0)
		return (1);		/* busy */

	if (sc->sc_dv_addr != 0xFF) {
		/* write function address */
		saf1761_otg_set_address(sc, sc->sc_dv_addr);
	}
	return (0);			/* complete */
}