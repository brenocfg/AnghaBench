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
struct ieee80211_frame {int dummy; } ;
struct bpf_hdr {int bh_hdrlen; int bh_caplen; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_CRC_LEN ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_FLAGS ; 
 int IEEE80211_RADIOTAP_F_FCS ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_TSFT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct ieee80211_frame*,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  possible_match (struct ieee80211_frame*,int,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int do_verify(struct ieee80211_frame *sent, int slen, void *got, int glen)
{
#define BIT(n)  (1<<(n))
	struct bpf_hdr *bpfh = got;
	struct ieee80211_frame *wh;
	struct ieee80211_radiotap_header *rth;
	int i;
	unsigned char *ptr, *ptr2;
	uint32_t present;
	uint8_t rflags;

	/* get the 802.11 header */
	glen -= bpfh->bh_hdrlen;
	assert(glen > 0);
	if (bpfh->bh_caplen != glen) {
		abort();
	}
	rth = (struct ieee80211_radiotap_header*)
	      ((char*) bpfh + bpfh->bh_hdrlen);
	glen -= rth->it_len;
	assert(glen > 0);
	wh = (struct ieee80211_frame*) ((char*)rth + rth->it_len);

        /* check if FCS/CRC is included in packet */
	present = le32toh(rth->it_present);
	if (present & BIT(IEEE80211_RADIOTAP_FLAGS)) {
		if (present & BIT(IEEE80211_RADIOTAP_TSFT))
			rflags = ((const uint8_t *)rth)[8];
		else
			rflags = ((const uint8_t *)rth)[0];
	} else  
		rflags = 0;
	if (rflags & IEEE80211_RADIOTAP_F_FCS)
		glen -= IEEE80211_CRC_LEN;
	assert(glen > 0);
	
	/* did we receive the packet we sent? */
	if (!possible_match(sent, slen, wh, glen))
		return 0;

	/* check if it got mangled */
	if (memcmp(sent, wh, slen) == 0) {
		printf("No mangling---got it perfect\n");
		return 1;
	}

	/* print differences */
	printf("Got mangled:\n");
	ptr = (unsigned char*) sent;
	ptr2 = (unsigned char *) wh;
	for (i = 0; i < slen; i++, ptr++, ptr2++) {
		if (*ptr != *ptr2)
			printf("Position: %d Was: %.2X Got: %.2X\n",
			       i, *ptr, *ptr2);
	}
	return -1;
#undef BIT
}