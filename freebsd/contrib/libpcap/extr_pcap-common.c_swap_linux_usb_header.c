#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ status; scalar_t__ offset; scalar_t__ len; } ;
typedef  TYPE_3__ usb_isodesc ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {scalar_t__ caplen; } ;
struct TYPE_5__ {scalar_t__ error_count; scalar_t__ numdesc; } ;
struct TYPE_6__ {TYPE_1__ iso; } ;
struct TYPE_8__ {scalar_t__ ts_usec; scalar_t__ status; scalar_t__ urb_len; scalar_t__ data_len; scalar_t__ transfer_type; scalar_t__ interval; scalar_t__ start_frame; scalar_t__ xfer_flags; scalar_t__ ndesc; TYPE_2__ s; void* ts_sec; int /*<<< orphan*/  bus_id; void* id; } ;
typedef  TYPE_4__ pcap_usb_header_mmapped ;
typedef  scalar_t__ bpf_u_int32 ;

/* Variables and functions */
 void* SWAPLL (void*) ; 
 void* SWAPLONG (scalar_t__) ; 
 int /*<<< orphan*/  SWAPSHORT (int /*<<< orphan*/ ) ; 
 scalar_t__ URB_ISOCHRONOUS ; 

__attribute__((used)) static void
swap_linux_usb_header(const struct pcap_pkthdr *hdr, u_char *buf,
    int header_len_64_bytes)
{
	pcap_usb_header_mmapped *uhdr = (pcap_usb_header_mmapped *)buf;
	bpf_u_int32 offset = 0;

	/*
	 * "offset" is the offset *past* the field we're swapping;
	 * we skip the field *before* checking to make sure
	 * the captured data length includes the entire field.
	 */

	/*
	 * The URB id is a totally opaque value; do we really need to
	 * convert it to the reading host's byte order???
	 */
	offset += 8;			/* skip past id */
	if (hdr->caplen < offset)
		return;
	uhdr->id = SWAPLL(uhdr->id);

	offset += 4;			/* skip past various 1-byte fields */

	offset += 2;			/* skip past bus_id */
	if (hdr->caplen < offset)
		return;
	uhdr->bus_id = SWAPSHORT(uhdr->bus_id);

	offset += 2;			/* skip past various 1-byte fields */

	offset += 8;			/* skip past ts_sec */
	if (hdr->caplen < offset)
		return;
	uhdr->ts_sec = SWAPLL(uhdr->ts_sec);

	offset += 4;			/* skip past ts_usec */
	if (hdr->caplen < offset)
		return;
	uhdr->ts_usec = SWAPLONG(uhdr->ts_usec);

	offset += 4;			/* skip past status */
	if (hdr->caplen < offset)
		return;
	uhdr->status = SWAPLONG(uhdr->status);

	offset += 4;			/* skip past urb_len */
	if (hdr->caplen < offset)
		return;
	uhdr->urb_len = SWAPLONG(uhdr->urb_len);

	offset += 4;			/* skip past data_len */
	if (hdr->caplen < offset)
		return;
	uhdr->data_len = SWAPLONG(uhdr->data_len);

	if (uhdr->transfer_type == URB_ISOCHRONOUS) {
		offset += 4;			/* skip past s.iso.error_count */
		if (hdr->caplen < offset)
			return;
		uhdr->s.iso.error_count = SWAPLONG(uhdr->s.iso.error_count);

		offset += 4;			/* skip past s.iso.numdesc */
		if (hdr->caplen < offset)
			return;
		uhdr->s.iso.numdesc = SWAPLONG(uhdr->s.iso.numdesc);
	} else
		offset += 8;			/* skip USB setup header */

	/*
	 * With the old header, there are no isochronous descriptors
	 * after the header.
	 *
	 * With the new header, the actual number of descriptors in
	 * the header is not s.iso.numdesc, it's ndesc - only the
	 * first N descriptors, for some value of N, are put into
	 * the header, and ndesc is set to the actual number copied.
	 * In addition, if s.iso.numdesc is negative, no descriptors
	 * are captured, and ndesc is set to 0.
	 */
	if (header_len_64_bytes) {
		/*
		 * This is either the "version 1" header, with
		 * 16 bytes of additional fields at the end, or
		 * a "version 0" header from a memory-mapped
		 * capture, with 16 bytes of zeroed-out padding
		 * at the end.  Byte swap them as if this were
		 * a "version 1" header.
		 */
		offset += 4;			/* skip past interval */
		if (hdr->caplen < offset)
			return;
		uhdr->interval = SWAPLONG(uhdr->interval);

		offset += 4;			/* skip past start_frame */
		if (hdr->caplen < offset)
			return;
		uhdr->start_frame = SWAPLONG(uhdr->start_frame);

		offset += 4;			/* skip past xfer_flags */
		if (hdr->caplen < offset)
			return;
		uhdr->xfer_flags = SWAPLONG(uhdr->xfer_flags);

		offset += 4;			/* skip past ndesc */
		if (hdr->caplen < offset)
			return;
		uhdr->ndesc = SWAPLONG(uhdr->ndesc);

		if (uhdr->transfer_type == URB_ISOCHRONOUS) {
			/* swap the values in struct linux_usb_isodesc */
			usb_isodesc *pisodesc;
			uint32_t i;

			pisodesc = (usb_isodesc *)(void *)(buf+offset);
			for (i = 0; i < uhdr->ndesc; i++) {
				offset += 4;		/* skip past status */
				if (hdr->caplen < offset)
					return;
				pisodesc->status = SWAPLONG(pisodesc->status);

				offset += 4;		/* skip past offset */
				if (hdr->caplen < offset)
					return;
				pisodesc->offset = SWAPLONG(pisodesc->offset);

				offset += 4;		/* skip past len */
				if (hdr->caplen < offset)
					return;
				pisodesc->len = SWAPLONG(pisodesc->len);

				offset += 4;		/* skip past padding */

				pisodesc++;
			}
		}
	}
}