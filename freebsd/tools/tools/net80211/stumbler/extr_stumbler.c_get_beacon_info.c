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
struct node_info {unsigned char chan; scalar_t__ wep; scalar_t__* ssid; } ;
struct ieee80211_ie_wpa {unsigned char* wpa_oui; scalar_t__ wpa_type; int /*<<< orphan*/  wpa_uciphercnt; scalar_t__ wpa_mcipher; int /*<<< orphan*/  wpa_version; } ;

/* Variables and functions */
 scalar_t__ CRYPT_80211i ; 
 scalar_t__ CRYPT_80211i_TKIP ; 
 scalar_t__ CRYPT_80211i_TKIP_PSK ; 
 scalar_t__ CRYPT_NONE ; 
 scalar_t__ CRYPT_WEP ; 
 scalar_t__ CRYPT_WPA1 ; 
 scalar_t__ CRYPT_WPA1_CCMP ; 
 scalar_t__ CRYPT_WPA1_CCMP_PSK ; 
 scalar_t__ CRYPT_WPA1_TKIP ; 
 scalar_t__ CRYPT_WPA1_TKIP_PSK ; 
 int IEEE80211_BEACON_CAPABILITY (unsigned char*) ; 
 int IEEE80211_CAPINFO_PRIVACY ; 
 int WPA_ASE_8021X_PSK ; 
 int WPA_CSE_CCMP ; 
 int WPA_CSE_TKIP ; 
 scalar_t__ WPA_OUI_TYPE ; 
 int WPA_VERSION ; 
 int /*<<< orphan*/  assert (int) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,unsigned char*,int) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char*) ; 

void get_beacon_info(unsigned char* data, int rd, 
		     struct node_info* node) {

	int blen = 8 + 2 + 2;
	
	strcpy(node->ssid, "<hidden>");
	node->chan = 0;
	node->wep = CRYPT_NONE;

	assert(rd >= blen);

	if (IEEE80211_BEACON_CAPABILITY(data) & IEEE80211_CAPINFO_PRIVACY)
		node->wep = CRYPT_WEP;

	data += blen;
	rd -= blen;

	while (rd > 2) {
                int eid, elen;

                eid = *data;
                data++;
                elen = *data;
                data++;
                rd -= 2;

		// short!
                if (rd < elen) {
                        return;
                }

                // ssid
                if (eid == 0) {
			if (elen == 1 && data[0] == 0) {
			// hidden
			}
			else {
                        	memcpy(node->ssid, data, elen);
                        	node->ssid[elen] = 0;
			}	
                }
                // chan
                else if(eid == 3) {
			// weird chan!
                        if( elen != 1) 
				goto next;

                        node->chan = *data;
                }
		// WPA 
		else if (eid == 221 && node->wep == CRYPT_WEP) {
			struct ieee80211_ie_wpa* wpa;

			wpa = (struct ieee80211_ie_wpa*) data;
			if (elen < 6)
				goto next;
			
			if (!memcmp(wpa->wpa_oui, "\x00\x50\xf2", 3)) {
			//	node->wep = CRYPT_WPA;
			}	
			else
				goto next;

			if (wpa->wpa_type == WPA_OUI_TYPE &&
			    le16toh(wpa->wpa_version) == WPA_VERSION) {
			    	int cipher, auth;
				unsigned char* ptr;
				
				node->wep = CRYPT_WPA1;
				
				if (elen < 12)
					goto next;

				cipher = ((unsigned char*) wpa->wpa_mcipher)[3];

				ptr = (unsigned char*)wpa + 12 + 
				      4 * le16toh(wpa->wpa_uciphercnt);
				
				if (elen < (ptr - data + 6))
					goto next;

				if ( *((unsigned short*) ptr) == 0)
					goto next;

				ptr += 2 + 3;
				auth = *ptr;

				if (cipher == WPA_CSE_TKIP) {
					node->wep = CRYPT_WPA1_TKIP;
					
					if (auth == WPA_ASE_8021X_PSK)
						node->wep = CRYPT_WPA1_TKIP_PSK;
				}

				if (cipher == WPA_CSE_CCMP) {
					node->wep = CRYPT_WPA1_CCMP;
					
					if (auth == WPA_ASE_8021X_PSK)
						node->wep = CRYPT_WPA1_CCMP_PSK;
				}
			}
		}
		else if (eid == 48 && node->wep == CRYPT_WEP) {
			unsigned char* ptr;

			// XXX no bounds checking
			ptr = data;

			if (ptr[0] == 1 && ptr[1] == 0) {
				unsigned short* count;
				int cipher = 0;

				ptr += 2;
				node->wep = CRYPT_80211i;

				if (!memcmp(ptr, "\x00\x0f\xac\x02", 4)) {
					node->wep = CRYPT_80211i_TKIP;
					cipher = 1;
				}

				ptr += 4;
				count = (unsigned short*) ptr;
				ptr +=2 + *count*4;

				count = (unsigned short*) ptr;
				if (*count) {
					ptr += 2;

					if (!memcmp(ptr,"\x00\x0f\xac\x02", 4)) {
						if (cipher)
							node->wep = CRYPT_80211i_TKIP_PSK;
					}
				}
			}
		}

next:
                data += elen;
                rd -= elen;
	}
}