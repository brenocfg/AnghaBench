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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct libusb_transfer {scalar_t__ num_iso_packets; size_t actual_length; int /*<<< orphan*/  endpoint; TYPE_1__* iso_packet_desc; int /*<<< orphan*/ * buffer; } ;
struct libusb_super_transfer {int /*<<< orphan*/  rem_len; } ;
struct libusb20_transfer {int dummy; } ;
struct TYPE_2__ {size_t length; int /*<<< orphan*/  actual_length; } ;

/* Variables and functions */
#define  LIBUSB20_TRANSFER_COMPLETED 129 
#define  LIBUSB20_TRANSFER_START 128 
 int /*<<< orphan*/  LIBUSB_TRANSFER_COMPLETED ; 
 int /*<<< orphan*/  libusb10_complete_transfer (struct libusb20_transfer*,struct libusb_super_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb10_convert_error (int) ; 
 int /*<<< orphan*/  libusb10_submit_transfer_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t libusb20_tr_get_actual_length (struct libusb20_transfer*) ; 
 int /*<<< orphan*/  libusb20_tr_get_length (struct libusb20_transfer*,scalar_t__) ; 
 scalar_t__ libusb20_tr_get_max_frames (struct libusb20_transfer*) ; 
 int /*<<< orphan*/  libusb20_tr_get_priv_sc0 (struct libusb20_transfer*) ; 
 struct libusb_super_transfer* libusb20_tr_get_priv_sc1 (struct libusb20_transfer*) ; 
 int libusb20_tr_get_status (struct libusb20_transfer*) ; 
 int /*<<< orphan*/  libusb20_tr_set_total_frames (struct libusb20_transfer*,scalar_t__) ; 
 int /*<<< orphan*/  libusb20_tr_setup_isoc (struct libusb20_transfer*,int /*<<< orphan*/ *,size_t,scalar_t__) ; 
 int /*<<< orphan*/  libusb20_tr_submit (struct libusb20_transfer*) ; 

__attribute__((used)) static void
libusb10_isoc_proxy(struct libusb20_transfer *pxfer)
{
	struct libusb_super_transfer *sxfer;
	struct libusb_transfer *uxfer;
	uint32_t actlen;
	uint16_t iso_packets;
	uint16_t i;
	uint8_t status;

	status = libusb20_tr_get_status(pxfer);
	sxfer = libusb20_tr_get_priv_sc1(pxfer);
	actlen = libusb20_tr_get_actual_length(pxfer);
	iso_packets = libusb20_tr_get_max_frames(pxfer);

	if (sxfer == NULL)
		return; /* cancelled - nothing to do */

	uxfer = (struct libusb_transfer *)(
	    ((uint8_t *)sxfer) + sizeof(*sxfer));

	if (iso_packets > uxfer->num_iso_packets)
		iso_packets = uxfer->num_iso_packets;

	if (iso_packets == 0)
		return; /* nothing to do */

	/* make sure that the number of ISOCHRONOUS packets is valid */
	uxfer->num_iso_packets = iso_packets;

	switch (status) {
	case LIBUSB20_TRANSFER_COMPLETED:
		/* update actual length */
		uxfer->actual_length = actlen;
		for (i = 0; i != iso_packets; i++) {
			uxfer->iso_packet_desc[i].actual_length =
			    libusb20_tr_get_length(pxfer, i);
		}
		libusb10_complete_transfer(pxfer, sxfer, LIBUSB_TRANSFER_COMPLETED);
		break;
	case LIBUSB20_TRANSFER_START:
		/* setup length(s) */
		actlen = 0;
		for (i = 0; i != iso_packets; i++) {
			libusb20_tr_setup_isoc(pxfer,
			    &uxfer->buffer[actlen],
			    uxfer->iso_packet_desc[i].length, i);
			actlen += uxfer->iso_packet_desc[i].length;
		}

		/* no remainder */
		sxfer->rem_len = 0;

		libusb20_tr_set_total_frames(pxfer, iso_packets);
		libusb20_tr_submit(pxfer);

		/* fork another USB transfer, if any */
		libusb10_submit_transfer_sub(libusb20_tr_get_priv_sc0(pxfer), uxfer->endpoint);
		break;
	default:
		libusb10_complete_transfer(pxfer, sxfer, libusb10_convert_error(status));
		break;
	}
}