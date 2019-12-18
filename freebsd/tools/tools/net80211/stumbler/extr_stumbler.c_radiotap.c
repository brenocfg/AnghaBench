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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct node_info {int signal; } ;
struct ieee80211_radiotap_header {int it_len; int it_present; } ;
struct ieee80211_frame {int dummy; } ;
typedef  int int8_t ;

/* Variables and functions */
#define  IEEE80211_RADIOTAP_CHANNEL 137 
#define  IEEE80211_RADIOTAP_DBM_ANTNOISE 136 
#define  IEEE80211_RADIOTAP_DBM_ANTSIGNAL 135 
#define  IEEE80211_RADIOTAP_DB_ANTNOISE 134 
#define  IEEE80211_RADIOTAP_DB_ANTSIGNAL 133 
#define  IEEE80211_RADIOTAP_EXT 132 
#define  IEEE80211_RADIOTAP_FHSS 131 
#define  IEEE80211_RADIOTAP_FLAGS 130 
#define  IEEE80211_RADIOTAP_RATE 129 
#define  IEEE80211_RADIOTAP_TSFT 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_packet_info (struct ieee80211_frame*,char*,int,struct node_info*) ; 
 int /*<<< orphan*/  mvprintw (int,int,char*,int) ; 
 int /*<<< orphan*/  update_node (struct node_info*) ; 

void radiotap(unsigned char* data, int rd) {
	struct ieee80211_radiotap_header* rth;
	struct ieee80211_frame* wh;
	char* body;
	struct node_info node;
	int8_t signal_dbm, noise_dbm;
	uint8_t signal_db, noise_db;
	int dbm = 0;
	int signal = 0;
	int i;

	rd -= 4; // 802.11 CRC

	// radiotap
	rth = (struct ieee80211_radiotap_header*) data;

	// 802.11
	wh = (struct ieee80211_frame*)
	     ((char*)rth + rth->it_len);
        rd -= rth->it_len;

	assert (rd >= 0);

	// body
	body = (char*) wh + sizeof(*wh);
	rd -= sizeof(*wh);

	if (!get_packet_info(wh, body, rd, &node))
		return;

	// signal and noise
	body = (char*) rth + sizeof(*rth);
	signal_dbm = noise_dbm = signal_db = noise_db = 0;

	for (i = IEEE80211_RADIOTAP_TSFT; i <= IEEE80211_RADIOTAP_EXT; i++) {
		if (!(rth->it_present & (1 << i)))
			continue;
		
		switch (i) {
		case IEEE80211_RADIOTAP_TSFT:
			body += sizeof(uint64_t);
			break;
		
		case IEEE80211_RADIOTAP_FLAGS:
		case IEEE80211_RADIOTAP_RATE:
			body += sizeof(uint8_t);
			break;
		
		case IEEE80211_RADIOTAP_CHANNEL:
			body += sizeof(uint16_t)*2;
			break;
		
		case IEEE80211_RADIOTAP_FHSS:
			body += sizeof(uint16_t);
			break;
		
		case IEEE80211_RADIOTAP_DBM_ANTSIGNAL:
			signal_dbm = *body;
			body++;
			dbm = 1;
			break;
		
		case IEEE80211_RADIOTAP_DBM_ANTNOISE:
			noise_dbm = *body;
			body++;
			break;
		
		case IEEE80211_RADIOTAP_DB_ANTSIGNAL:
			signal_db = *((unsigned char*)body);
			body++;
			break;

		case IEEE80211_RADIOTAP_DB_ANTNOISE:
			noise_db = *((unsigned char*)body);
			body++;
			break;
		
		case IEEE80211_RADIOTAP_EXT:
			abort();
			break;
		}
	}
	if (dbm) {
		signal = signal_dbm - noise_dbm;
	}
	else {
		signal = signal_db - noise_db;
	}
	if (signal < 0)
		signal = 0;

	node.signal = signal;
#if 0
	if (node.signal > 100 || node.signal < 0) {
		mvprintw(25,25, "sig=%d", node.signal);
	}	
#else		
	assert (node.signal <= 100 && node.signal >= 0);
#endif

	update_node(&node);
}