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
typedef  int u8 ;
struct eap_sake_parse_attr {int const* rand_s; int const* rand_p; int const* mic_s; int const* mic_p; int const* serverid; int serverid_len; int const* peerid; int peerid_len; int const* spi_s; int spi_s_len; int const* spi_p; int spi_p_len; int const* any_id_req; int const* perm_id_req; int const* encr_data; int encr_data_len; int const* iv; int iv_len; int const* next_tmpid; int next_tmpid_len; int const* msk_life; } ;

/* Variables and functions */
#define  EAP_SAKE_AT_ANY_ID_REQ 142 
#define  EAP_SAKE_AT_ENCR_DATA 141 
#define  EAP_SAKE_AT_IV 140 
#define  EAP_SAKE_AT_MIC_P 139 
#define  EAP_SAKE_AT_MIC_S 138 
#define  EAP_SAKE_AT_MSK_LIFE 137 
#define  EAP_SAKE_AT_NEXT_TMPID 136 
#define  EAP_SAKE_AT_PADDING 135 
#define  EAP_SAKE_AT_PEERID 134 
#define  EAP_SAKE_AT_PERM_ID_REQ 133 
#define  EAP_SAKE_AT_RAND_P 132 
#define  EAP_SAKE_AT_RAND_S 131 
#define  EAP_SAKE_AT_SERVERID 130 
#define  EAP_SAKE_AT_SPI_P 129 
#define  EAP_SAKE_AT_SPI_S 128 
 int EAP_SAKE_MIC_LEN ; 
 int EAP_SAKE_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_sake_parse_add_attr(struct eap_sake_parse_attr *attr,
				   u8 attr_id, u8 len, const u8 *data)
{
	size_t i;

	switch (attr_id) {
	case EAP_SAKE_AT_RAND_S:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_RAND_S");
		if (len != EAP_SAKE_RAND_LEN) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: AT_RAND_S with "
				   "invalid payload length %d", len);
			return -1;
		}
		attr->rand_s = data;
		break;
	case EAP_SAKE_AT_RAND_P:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_RAND_P");
		if (len != EAP_SAKE_RAND_LEN) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: AT_RAND_P with "
				   "invalid payload length %d", len);
			return -1;
		}
		attr->rand_p = data;
		break;
	case EAP_SAKE_AT_MIC_S:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_MIC_S");
		if (len != EAP_SAKE_MIC_LEN) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: AT_MIC_S with "
				   "invalid payload length %d", len);
			return -1;
		}
		attr->mic_s = data;
		break;
	case EAP_SAKE_AT_MIC_P:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_MIC_P");
		if (len != EAP_SAKE_MIC_LEN) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: AT_MIC_P with "
				   "invalid payload length %d", len);
			return -1;
		}
		attr->mic_p = data;
		break;
	case EAP_SAKE_AT_SERVERID:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_SERVERID");
		attr->serverid = data;
		attr->serverid_len = len;
		break;
	case EAP_SAKE_AT_PEERID:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_PEERID");
		attr->peerid = data;
		attr->peerid_len = len;
		break;
	case EAP_SAKE_AT_SPI_S:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_SPI_S");
		attr->spi_s = data;
		attr->spi_s_len = len;
		break;
	case EAP_SAKE_AT_SPI_P:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_SPI_P");
		attr->spi_p = data;
		attr->spi_p_len = len;
		break;
	case EAP_SAKE_AT_ANY_ID_REQ:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_ANY_ID_REQ");
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: Invalid AT_ANY_ID_REQ"
				   " payload length %d", len);
			return -1;
		}
		attr->any_id_req = data;
		break;
	case EAP_SAKE_AT_PERM_ID_REQ:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_PERM_ID_REQ");
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: Invalid "
				   "AT_PERM_ID_REQ payload length %d", len);
			return -1;
		}
		attr->perm_id_req = data;
		break;
	case EAP_SAKE_AT_ENCR_DATA:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_ENCR_DATA");
		attr->encr_data = data;
		attr->encr_data_len = len;
		break;
	case EAP_SAKE_AT_IV:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_IV");
		attr->iv = data;
		attr->iv_len = len;
		break;
	case EAP_SAKE_AT_PADDING:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_PADDING");
		for (i = 0; i < len; i++) {
			if (data[i]) {
				wpa_printf(MSG_DEBUG, "EAP-SAKE: AT_PADDING "
					   "with non-zero pad byte");
				return -1;
			}
		}
		break;
	case EAP_SAKE_AT_NEXT_TMPID:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_NEXT_TMPID");
		attr->next_tmpid = data;
		attr->next_tmpid_len = len;
		break;
	case EAP_SAKE_AT_MSK_LIFE:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Parse: AT_MSK_LIFE");
		if (len != 4) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: Invalid "
				   "AT_MSK_LIFE payload length %d", len);
			return -1;
		}
		attr->msk_life = data;
		break;
	default:
		if (attr_id < 128) {
			wpa_printf(MSG_DEBUG, "EAP-SAKE: Unknown non-skippable"
				   " attribute %d", attr_id);
			return -1;
		}
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Ignoring unknown skippable "
			   "attribute %d", attr_id);
		break;
	}

	if (attr->iv && !attr->encr_data) {
		wpa_printf(MSG_DEBUG, "EAP-SAKE: AT_IV included without "
			   "AT_ENCR_DATA");
		return -1;
	}

	return 0;
}