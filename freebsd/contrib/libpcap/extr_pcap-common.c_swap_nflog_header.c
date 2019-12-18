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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int caplen; int len; } ;
struct TYPE_3__ {int tlv_type; int tlv_length; } ;
typedef  TYPE_1__ nflog_tlv_t ;
struct TYPE_4__ {scalar_t__ nflog_version; } ;
typedef  TYPE_2__ nflog_hdr_t ;

/* Variables and functions */
 void* SWAPSHORT (int) ; 

__attribute__((used)) static void
swap_nflog_header(const struct pcap_pkthdr *hdr, u_char *buf)
{
	u_char *p = buf;
	nflog_hdr_t *nfhdr = (nflog_hdr_t *)buf;
	nflog_tlv_t *tlv;
	u_int caplen = hdr->caplen;
	u_int length = hdr->len;
	uint16_t size;

	if (caplen < (u_int) sizeof(nflog_hdr_t) ||
	    length < (u_int) sizeof(nflog_hdr_t)) {
		/* Not enough data to have any TLVs. */
		return;
	}

	if (nfhdr->nflog_version != 0) {
		/* Unknown NFLOG version */
		return;
	}

	length -= sizeof(nflog_hdr_t);
	caplen -= sizeof(nflog_hdr_t);
	p += sizeof(nflog_hdr_t);

	while (caplen >= sizeof(nflog_tlv_t)) {
		tlv = (nflog_tlv_t *) p;

		/* Swap the type and length. */
		tlv->tlv_type = SWAPSHORT(tlv->tlv_type);
		tlv->tlv_length = SWAPSHORT(tlv->tlv_length);

		/* Get the length of the TLV. */
		size = tlv->tlv_length;
		if (size % 4 != 0)
			size += 4 - size % 4;

		/* Is the TLV's length less than the minimum? */
		if (size < sizeof(nflog_tlv_t)) {
			/* Yes. Give up now. */
			return;
		}

		/* Do we have enough data for the full TLV? */
		if (caplen < size || length < size) {
			/* No. */
			return;
		}

		/* Skip over the TLV. */
		length -= size;
		caplen -= size;
		p += size;
	}
}