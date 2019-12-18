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
struct ieee80211_radiotap_header {int it_len; int /*<<< orphan*/  it_present; } ;
struct bpf_hdr {int bh_hdrlen; int bh_caplen; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_CRC_LEN ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_FLAGS ; 
 int IEEE80211_RADIOTAP_F_FCS ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_TSFT ; 
 int /*<<< orphan*/  assert (int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 

void *get_wifi(void *buf, int *len)
{
#define	BIT(n)	(1<<(n))
	struct bpf_hdr* bpfh = (struct bpf_hdr*) buf;
	struct ieee80211_radiotap_header* rth;
	uint32_t present;
	uint8_t rflags;
	void *ptr;

	/* bpf */
	*len -= bpfh->bh_hdrlen;

	if (bpfh->bh_caplen != *len) {
		assert(bpfh->bh_caplen < *len);
		*len = bpfh->bh_caplen;
	}
	assert(bpfh->bh_caplen == *len);

	/* radiotap */
	rth = (struct ieee80211_radiotap_header*)
	      ((char*)bpfh + bpfh->bh_hdrlen);
	/* XXX cache; drivers won't change this per-packet */
	/* check if FCS/CRC is included in packet */
	present = le32toh(rth->it_present);
	if (present & BIT(IEEE80211_RADIOTAP_FLAGS)) {
		if (present & BIT(IEEE80211_RADIOTAP_TSFT))
			rflags = ((const uint8_t *)rth)[8];
		else
			rflags = ((const uint8_t *)rth)[0];
	} else
		rflags = 0;
	*len -= rth->it_len;

	/* 802.11 CRC */
	if (rflags & IEEE80211_RADIOTAP_F_FCS)
		*len -= IEEE80211_CRC_LEN;

	ptr = (char*)rth + rth->it_len;
	return ptr;
#undef BIT
}