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
struct saf1761_otg_td {int ep_index; int remainder; int error_any; int max_packet_size; int short_pkt; scalar_t__ set_toggle; } ;
struct saf1761_otg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int SAF1761_READ_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAF1761_WRITE_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOTG_BUF_LENGTH ; 
 int SOTG_BUF_LENGTH_BUFLEN_MASK ; 
 int SOTG_BUF_LENGTH_FILLED_MASK ; 
 int /*<<< orphan*/  SOTG_CTRL_FUNC ; 
 int SOTG_CTRL_FUNC_DSEN ; 
 int /*<<< orphan*/  SOTG_EP_INDEX ; 
 int SOTG_EP_INDEX_DIR_OUT ; 
 int SOTG_EP_INDEX_ENDP_INDEX_SHIFT ; 
 int SOTG_EP_INDEX_EP0SETUP ; 
 int /*<<< orphan*/  saf1761_read_device_fifo (struct saf1761_otg_softc*,struct saf1761_otg_td*,int) ; 

__attribute__((used)) static uint8_t
saf1761_device_data_rx(struct saf1761_otg_softc *sc, struct saf1761_otg_td *td)
{
	uint32_t count;
	uint8_t got_short = 0;

	if (td->ep_index == 0) {
		/* select the correct endpoint */
		SAF1761_WRITE_LE_4(sc, SOTG_EP_INDEX, SOTG_EP_INDEX_EP0SETUP);

		count = SAF1761_READ_LE_4(sc, SOTG_BUF_LENGTH);

		/* check buffer status */
		if ((count & SOTG_BUF_LENGTH_FILLED_MASK) != 0) {

			if (td->remainder == 0) {
				/*
				 * We are actually complete and have
				 * received the next SETUP:
				 */
				DPRINTFN(5, "faking complete\n");
				return (0);	/* complete */
			}
			DPRINTFN(5, "SETUP packet while receiving data\n");
			/*
			 * USB Host Aborted the transfer.
			 */
			td->error_any = 1;
			return (0);	/* complete */
		}
	}
	/* select the correct endpoint */
	SAF1761_WRITE_LE_4(sc, SOTG_EP_INDEX,
	    (td->ep_index << SOTG_EP_INDEX_ENDP_INDEX_SHIFT) |
	    SOTG_EP_INDEX_DIR_OUT);

	/* enable data stage */
	if (td->set_toggle) {
		td->set_toggle = 0;
		SAF1761_WRITE_LE_4(sc, SOTG_CTRL_FUNC, SOTG_CTRL_FUNC_DSEN);
	}

	count = SAF1761_READ_LE_4(sc, SOTG_BUF_LENGTH);

	/* check buffer status */
	if ((count & SOTG_BUF_LENGTH_FILLED_MASK) == 0)
		return (1);		/* not complete */

	/* get buffer length */
	count &= SOTG_BUF_LENGTH_BUFLEN_MASK;

	DPRINTFN(5, "rem=%u count=0x%04x\n", td->remainder, count);

	/* verify the packet byte count */
	if (count != td->max_packet_size) {
		if (count < td->max_packet_size) {
			/* we have a short packet */
			td->short_pkt = 1;
			got_short = 1;
		} else {
			/* invalid USB packet */
			td->error_any = 1;
			return (0);	/* we are complete */
		}
	}
	/* verify the packet byte count */
	if (count > td->remainder) {
		/* invalid USB packet */
		td->error_any = 1;
		return (0);		/* we are complete */
	}
	/* receive data */
	saf1761_read_device_fifo(sc, td, count);

	/* check if we are complete */
	if ((td->remainder == 0) || got_short) {
		if (td->short_pkt) {
			/* we are complete */
			return (0);
		}
		/* else need to receive a zero length packet */
	}
	return (1);			/* not complete */
}