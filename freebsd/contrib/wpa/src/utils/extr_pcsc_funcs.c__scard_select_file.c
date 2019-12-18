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
struct scard_data {int dummy; } ;
typedef  scalar_t__ sim_types ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  get_resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 long SCARD_S_SUCCESS ; 
 scalar_t__ SCARD_USIM ; 
 unsigned char SIM_CMD_GET_RESPONSE ; 
 unsigned char SIM_CMD_SELECT ; 
 unsigned char USIM_CLA ; 
 int /*<<< orphan*/  os_memcpy (unsigned char*,unsigned char*,size_t) ; 
 long scard_transmit (struct scard_data*,unsigned char*,int,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int _scard_select_file(struct scard_data *scard, unsigned short file_id,
			      unsigned char *buf, size_t *buf_len,
			      sim_types sim_type, unsigned char *aid,
			      size_t aidlen)
{
	long ret;
	unsigned char resp[3];
	unsigned char cmd[50] = { SIM_CMD_SELECT };
	int cmdlen;
	unsigned char get_resp[5] = { SIM_CMD_GET_RESPONSE };
	size_t len, rlen;

	if (sim_type == SCARD_USIM) {
		cmd[0] = USIM_CLA;
		cmd[3] = 0x04;
		get_resp[0] = USIM_CLA;
	}

	wpa_printf(MSG_DEBUG, "SCARD: select file %04x", file_id);
	if (aid) {
		wpa_hexdump(MSG_DEBUG, "SCARD: select file by AID",
			    aid, aidlen);
		if (5 + aidlen > sizeof(cmd))
			return -1;
		cmd[2] = 0x04; /* Select by AID */
		cmd[4] = aidlen; /* len */
		os_memcpy(cmd + 5, aid, aidlen);
		cmdlen = 5 + aidlen;
	} else {
		cmd[5] = file_id >> 8;
		cmd[6] = file_id & 0xff;
		cmdlen = 7;
	}
	len = sizeof(resp);
	ret = scard_transmit(scard, cmd, cmdlen, resp, &len);
	if (ret != SCARD_S_SUCCESS) {
		wpa_printf(MSG_WARNING, "SCARD: SCardTransmit failed "
			   "(err=0x%lx)", ret);
		return -1;
	}

	if (len != 2) {
		wpa_printf(MSG_WARNING, "SCARD: unexpected resp len "
			   "%d (expected 2)", (int) len);
		return -1;
	}

	if (resp[0] == 0x98 && resp[1] == 0x04) {
		/* Security status not satisfied (PIN_WLAN) */
		wpa_printf(MSG_WARNING, "SCARD: Security status not satisfied "
			   "(PIN_WLAN)");
		return -1;
	}

	if (resp[0] == 0x6e) {
		wpa_printf(MSG_DEBUG, "SCARD: used CLA not supported");
		return -1;
	}

	if (resp[0] != 0x6c && resp[0] != 0x9f && resp[0] != 0x61) {
		wpa_printf(MSG_WARNING, "SCARD: unexpected response 0x%02x "
			   "(expected 0x61, 0x6c, or 0x9f)", resp[0]);
		return -1;
	}
	/* Normal ending of command; resp[1] bytes available */
	get_resp[4] = resp[1];
	wpa_printf(MSG_DEBUG, "SCARD: trying to get response (%d bytes)",
		   resp[1]);

	rlen = *buf_len;
	ret = scard_transmit(scard, get_resp, sizeof(get_resp), buf, &rlen);
	if (ret == SCARD_S_SUCCESS) {
		*buf_len = resp[1] < rlen ? resp[1] : rlen;
		return 0;
	}

	wpa_printf(MSG_WARNING, "SCARD: SCardTransmit err=0x%lx\n", ret);
	return -1;
}