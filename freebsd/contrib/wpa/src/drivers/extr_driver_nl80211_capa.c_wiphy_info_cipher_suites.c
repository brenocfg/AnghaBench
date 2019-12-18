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
typedef  int u32 ;
struct wiphy_info_data {TYPE_1__* capa; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  RSN_CIPHER_SUITE_AES_128_CMAC 139 
#define  RSN_CIPHER_SUITE_BIP_CMAC_256 138 
#define  RSN_CIPHER_SUITE_BIP_GMAC_128 137 
#define  RSN_CIPHER_SUITE_BIP_GMAC_256 136 
#define  RSN_CIPHER_SUITE_CCMP 135 
#define  RSN_CIPHER_SUITE_CCMP_256 134 
#define  RSN_CIPHER_SUITE_GCMP 133 
#define  RSN_CIPHER_SUITE_GCMP_256 132 
#define  RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED 131 
#define  RSN_CIPHER_SUITE_TKIP 130 
#define  RSN_CIPHER_SUITE_WEP104 129 
#define  RSN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_BIP ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_BIP_CMAC_256 ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_BIP_GMAC_128 ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_BIP_GMAC_256 ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_CCMP ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_CCMP_256 ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_GCMP ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_GCMP_256 ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_GTK_NOT_USED ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_TKIP ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_WEP104 ; 
 int /*<<< orphan*/  WPA_DRIVER_CAPA_ENC_WEP40 ; 
 int* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 

__attribute__((used)) static void wiphy_info_cipher_suites(struct wiphy_info_data *info,
				     struct nlattr *tb)
{
	int i, num;
	u32 *ciphers;

	if (tb == NULL)
		return;

	num = nla_len(tb) / sizeof(u32);
	ciphers = nla_data(tb);
	for (i = 0; i < num; i++) {
		u32 c = ciphers[i];

		wpa_printf(MSG_DEBUG, "nl80211: Supported cipher %02x-%02x-%02x:%d",
			   c >> 24, (c >> 16) & 0xff,
			   (c >> 8) & 0xff, c & 0xff);
		switch (c) {
		case RSN_CIPHER_SUITE_CCMP_256:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_CCMP_256;
			break;
		case RSN_CIPHER_SUITE_GCMP_256:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_GCMP_256;
			break;
		case RSN_CIPHER_SUITE_CCMP:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_CCMP;
			break;
		case RSN_CIPHER_SUITE_GCMP:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_GCMP;
			break;
		case RSN_CIPHER_SUITE_TKIP:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_TKIP;
			break;
		case RSN_CIPHER_SUITE_WEP104:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_WEP104;
			break;
		case RSN_CIPHER_SUITE_WEP40:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_WEP40;
			break;
		case RSN_CIPHER_SUITE_AES_128_CMAC:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_BIP;
			break;
		case RSN_CIPHER_SUITE_BIP_GMAC_128:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_BIP_GMAC_128;
			break;
		case RSN_CIPHER_SUITE_BIP_GMAC_256:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_BIP_GMAC_256;
			break;
		case RSN_CIPHER_SUITE_BIP_CMAC_256:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_BIP_CMAC_256;
			break;
		case RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED:
			info->capa->enc |= WPA_DRIVER_CAPA_ENC_GTK_NOT_USED;
			break;
		}
	}
}