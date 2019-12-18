#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int auth; size_t key_mgmt; int enc; int /*<<< orphan*/  flags; } ;
struct wpa_driver_ndis_data {int has_capability; TYPE_1__ capa; scalar_t__ no_of_pmkid; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int AuthModeSupported; int EncryptStatusSupported; } ;
struct TYPE_5__ {int Version; size_t NoOfAuthEncryptPairsSupported; TYPE_3__* AuthenticationEncryptionSupported; scalar_t__ NoOfPMKIDs; } ;
typedef  TYPE_2__ NDIS_802_11_CAPABILITY ;
typedef  TYPE_3__ NDIS_802_11_AUTHENTICATION_ENCRYPTION ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
#define  Ndis802_11AuthModeOpen 137 
#define  Ndis802_11AuthModeShared 136 
#define  Ndis802_11AuthModeWPA 135 
#define  Ndis802_11AuthModeWPA2 134 
#define  Ndis802_11AuthModeWPA2PSK 133 
#define  Ndis802_11AuthModeWPANone 132 
#define  Ndis802_11AuthModeWPAPSK 131 
#define  Ndis802_11Encryption1Enabled 130 
#define  Ndis802_11Encryption2Enabled 129 
#define  Ndis802_11Encryption3Enabled 128 
 int /*<<< orphan*/  OID_802_11_CAPABILITY ; 
 int WPA_DRIVER_AUTH_OPEN ; 
 int WPA_DRIVER_AUTH_SHARED ; 
 int WPA_DRIVER_CAPA_ENC_CCMP ; 
 int WPA_DRIVER_CAPA_ENC_TKIP ; 
 int WPA_DRIVER_CAPA_ENC_WEP104 ; 
 int WPA_DRIVER_CAPA_ENC_WEP40 ; 
 size_t WPA_DRIVER_CAPA_KEY_MGMT_WPA ; 
 size_t WPA_DRIVER_CAPA_KEY_MGMT_WPA2 ; 
 size_t WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK ; 
 size_t WPA_DRIVER_CAPA_KEY_MGMT_WPA_NONE ; 
 size_t WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_DRIVER_IE ; 
 int ndis_get_oid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_driver_ndis_get_wpa_capability (struct wpa_driver_ndis_data*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wpa_driver_ndis_get_capability(struct wpa_driver_ndis_data *drv)
{
	char buf[512];
	int len;
	size_t i;
	NDIS_802_11_CAPABILITY *c;

	drv->capa.flags = WPA_DRIVER_FLAGS_DRIVER_IE;

	len = ndis_get_oid(drv, OID_802_11_CAPABILITY, buf, sizeof(buf));
	if (len < 0) {
		wpa_driver_ndis_get_wpa_capability(drv);
		return;
	}

	wpa_hexdump(MSG_MSGDUMP, "OID_802_11_CAPABILITY", (u8 *) buf, len);
	c = (NDIS_802_11_CAPABILITY *) buf;
	if (len < sizeof(*c) || c->Version != 2) {
		wpa_printf(MSG_DEBUG, "NDIS: unsupported "
			   "OID_802_11_CAPABILITY data");
		return;
	}
	wpa_printf(MSG_DEBUG, "NDIS: Driver supports OID_802_11_CAPABILITY - "
		   "NoOfPMKIDs %d NoOfAuthEncrPairs %d",
		   (int) c->NoOfPMKIDs,
		   (int) c->NoOfAuthEncryptPairsSupported);
	drv->has_capability = 1;
	drv->no_of_pmkid = c->NoOfPMKIDs;
	for (i = 0; i < c->NoOfAuthEncryptPairsSupported; i++) {
		NDIS_802_11_AUTHENTICATION_ENCRYPTION *ae;
		ae = &c->AuthenticationEncryptionSupported[i];
		if ((char *) (ae + 1) > buf + len) {
			wpa_printf(MSG_DEBUG, "NDIS: auth/encr pair list "
				   "overflow");
			break;
		}
		wpa_printf(MSG_MSGDUMP, "NDIS: %d - auth %d encr %d",
			   i, (int) ae->AuthModeSupported,
			   (int) ae->EncryptStatusSupported);
		switch (ae->AuthModeSupported) {
		case Ndis802_11AuthModeOpen:
			drv->capa.auth |= WPA_DRIVER_AUTH_OPEN;
			break;
		case Ndis802_11AuthModeShared:
			drv->capa.auth |= WPA_DRIVER_AUTH_SHARED;
			break;
		case Ndis802_11AuthModeWPA:
			drv->capa.key_mgmt |= WPA_DRIVER_CAPA_KEY_MGMT_WPA;
			break;
		case Ndis802_11AuthModeWPAPSK:
			drv->capa.key_mgmt |= WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK;
			break;
		case Ndis802_11AuthModeWPA2:
			drv->capa.key_mgmt |= WPA_DRIVER_CAPA_KEY_MGMT_WPA2;
			break;
		case Ndis802_11AuthModeWPA2PSK:
			drv->capa.key_mgmt |=
				WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK;
			break;
		case Ndis802_11AuthModeWPANone:
			drv->capa.key_mgmt |=
				WPA_DRIVER_CAPA_KEY_MGMT_WPA_NONE;
			break;
		default:
			break;
		}
		switch (ae->EncryptStatusSupported) {
		case Ndis802_11Encryption1Enabled:
			drv->capa.enc |= WPA_DRIVER_CAPA_ENC_WEP40;
			drv->capa.enc |= WPA_DRIVER_CAPA_ENC_WEP104;
			break;
		case Ndis802_11Encryption2Enabled:
			drv->capa.enc |= WPA_DRIVER_CAPA_ENC_TKIP;
			break;
		case Ndis802_11Encryption3Enabled:
			drv->capa.enc |= WPA_DRIVER_CAPA_ENC_CCMP;
			break;
		default:
			break;
		}
	}

	wpa_printf(MSG_DEBUG, "NDIS: driver capabilities: key_mgmt 0x%x "
		   "enc 0x%x auth 0x%x",
		   drv->capa.key_mgmt, drv->capa.enc, drv->capa.auth);
}