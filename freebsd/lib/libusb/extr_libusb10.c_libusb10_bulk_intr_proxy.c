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
typedef  int /*<<< orphan*/  uint32_t ;
struct libusb_transfer {int flags; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  timeout; int /*<<< orphan*/  actual_length; } ;
struct libusb_super_transfer {int /*<<< orphan*/  rem_len; int /*<<< orphan*/  curr_data; int /*<<< orphan*/  last_len; } ;
struct libusb20_transfer {int dummy; } ;

/* Variables and functions */
#define  LIBUSB20_TRANSFER_COMPLETED 129 
#define  LIBUSB20_TRANSFER_START 128 
 int /*<<< orphan*/  LIBUSB_TRANSFER_COMPLETED ; 
 int /*<<< orphan*/  LIBUSB_TRANSFER_ERROR ; 
 int LIBUSB_TRANSFER_SHORT_NOT_OK ; 
 int /*<<< orphan*/  libusb10_complete_transfer (struct libusb20_transfer*,struct libusb_super_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb10_convert_error (int) ; 
 int /*<<< orphan*/  libusb10_submit_transfer_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_tr_get_actual_length (struct libusb20_transfer*) ; 
 int /*<<< orphan*/  libusb20_tr_get_max_total_length (struct libusb20_transfer*) ; 
 int /*<<< orphan*/  libusb20_tr_get_priv_sc0 (struct libusb20_transfer*) ; 
 struct libusb_super_transfer* libusb20_tr_get_priv_sc1 (struct libusb20_transfer*) ; 
 int libusb20_tr_get_status (struct libusb20_transfer*) ; 
 int /*<<< orphan*/  libusb20_tr_setup_bulk (struct libusb20_transfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_tr_submit (struct libusb20_transfer*) ; 

__attribute__((used)) static void
libusb10_bulk_intr_proxy(struct libusb20_transfer *pxfer)
{
	struct libusb_super_transfer *sxfer;
	struct libusb_transfer *uxfer;
	uint32_t max_bulk;
	uint32_t actlen;
	uint8_t status;
	uint8_t flags;

	status = libusb20_tr_get_status(pxfer);
	sxfer = libusb20_tr_get_priv_sc1(pxfer);
	max_bulk = libusb20_tr_get_max_total_length(pxfer);
	actlen = libusb20_tr_get_actual_length(pxfer);

	if (sxfer == NULL)
		return;			/* cancelled - nothing to do */

	uxfer = (struct libusb_transfer *)(
	    ((uint8_t *)sxfer) + sizeof(*sxfer));

	flags = uxfer->flags;

	switch (status) {
	case LIBUSB20_TRANSFER_COMPLETED:

		uxfer->actual_length += actlen;

		/* check for short packet */
		if (sxfer->last_len != actlen) {
			if (flags & LIBUSB_TRANSFER_SHORT_NOT_OK) {
				libusb10_complete_transfer(pxfer, sxfer, LIBUSB_TRANSFER_ERROR);
			} else {
				libusb10_complete_transfer(pxfer, sxfer, LIBUSB_TRANSFER_COMPLETED);
			}
			break;
		}
		/* check for end of data */
		if (sxfer->rem_len == 0) {
			libusb10_complete_transfer(pxfer, sxfer, LIBUSB_TRANSFER_COMPLETED);
			break;
		}
		/* FALLTHROUGH */

	case LIBUSB20_TRANSFER_START:
		if (max_bulk > sxfer->rem_len) {
			max_bulk = sxfer->rem_len;
		}
		/* setup new BULK or INTERRUPT transaction */
		libusb20_tr_setup_bulk(pxfer,
		    sxfer->curr_data, max_bulk, uxfer->timeout);

		/* update counters */
		sxfer->last_len = max_bulk;
		sxfer->curr_data += max_bulk;
		sxfer->rem_len -= max_bulk;

		libusb20_tr_submit(pxfer);

		/* check if we can fork another USB transfer */
		if (sxfer->rem_len == 0)
			libusb10_submit_transfer_sub(libusb20_tr_get_priv_sc0(pxfer), uxfer->endpoint);
		break;

	default:
		libusb10_complete_transfer(pxfer, sxfer, libusb10_convert_error(status));
		break;
	}
}