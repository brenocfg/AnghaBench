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
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
#define  CRYPT_80211i 138 
#define  CRYPT_80211i_TKIP 137 
#define  CRYPT_80211i_TKIP_PSK 136 
#define  CRYPT_NONE 135 
#define  CRYPT_WEP 134 
#define  CRYPT_WPA 133 
#define  CRYPT_WPA1 132 
#define  CRYPT_WPA1_CCMP 131 
#define  CRYPT_WPA1_CCMP_PSK 130 
#define  CRYPT_WPA1_TKIP 129 
#define  CRYPT_WPA1_TKIP_PSK 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int strlen (char*) ; 

char* wep2str(int w) {
	char* wep = 0;
	static char res[14];

	switch (w) {
	case CRYPT_NONE:
		wep = "";
		break;

	case CRYPT_WEP:
		wep = "WEP";
		break;
		
	case CRYPT_WPA1:
		wep = "WPA1";
		break;
	
	case CRYPT_WPA:
		wep = "WPA?";
		break;

	case CRYPT_WPA1_TKIP:
		wep = "WPA1-TKIP";
		break;
	
	case CRYPT_WPA1_TKIP_PSK:
		wep = "WPA1-TKIP-PSK";
		break;

	case CRYPT_WPA1_CCMP:
		wep = "WPA1-CCMP";
		break;

	case CRYPT_WPA1_CCMP_PSK:
		wep = "WPA1-CCMP-PSK";
		break;

	case CRYPT_80211i:
		wep = "i";
		break;

	case CRYPT_80211i_TKIP:
		wep = "11i-TKIP";
		break;
	
	case CRYPT_80211i_TKIP_PSK:
		wep = "11i-TKIP-PSK";
		break;

	default:
		wep = "FIXME!";
		break;
	}

	memset(res, ' ', sizeof(res));
	assert(strlen(wep) < sizeof(res));
	memcpy(res, wep, strlen(wep));
	res[sizeof(res)-1] = 0;
	return res;
}