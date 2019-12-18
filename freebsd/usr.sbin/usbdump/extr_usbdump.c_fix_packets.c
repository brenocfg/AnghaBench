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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  temp ;
struct header_32 {int hdrlen; int align; void* datalen; void* caplen; void* ts_usec; void* ts_sec; } ;
struct TYPE_2__ {int tv_sec; int tv_usec; } ;
struct bpf_hdr {int bh_caplen; int bh_datalen; int bh_hdrlen; TYPE_1__ bh_tstamp; } ;

/* Variables and functions */
 int BPF_WORDALIGN (int) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct header_32*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fix_packets(uint8_t *data, const int datalen)
{
	struct header_32 temp;
	uint8_t *ptr;
	uint8_t *next;
	uint32_t hdrlen;
	uint32_t caplen;

	for (ptr = data; ptr < (data + datalen); ptr = next) {

		const struct bpf_hdr *hdr;

		hdr = (const struct bpf_hdr *)ptr;

		temp.ts_sec = htole32(hdr->bh_tstamp.tv_sec);
		temp.ts_usec = htole32(hdr->bh_tstamp.tv_usec);
		temp.caplen = htole32(hdr->bh_caplen);
		temp.datalen = htole32(hdr->bh_datalen);
		temp.hdrlen = hdr->bh_hdrlen;
		temp.align = BPF_WORDALIGN(1);

		hdrlen = hdr->bh_hdrlen;
		caplen = hdr->bh_caplen;

		if ((hdrlen >= sizeof(temp)) && (hdrlen <= 255) &&
		    ((ptr + hdrlen) <= (data + datalen))) {
			memcpy(ptr, &temp, sizeof(temp));
			memset(ptr + sizeof(temp), 0, hdrlen - sizeof(temp));
		} else {
			err(EXIT_FAILURE, "Invalid header length %d", hdrlen);
		}

		next = ptr + BPF_WORDALIGN(hdrlen + caplen);

		if (next <= ptr)
			err(EXIT_FAILURE, "Invalid length");
	}
}