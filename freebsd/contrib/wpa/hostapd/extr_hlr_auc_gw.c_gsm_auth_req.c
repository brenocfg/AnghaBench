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
typedef  int /*<<< orphan*/  u8 ;
struct milenage_parameters {int /*<<< orphan*/  ki; int /*<<< orphan*/  opc; } ;

/* Variables and functions */
 int EAP_SIM_MAX_CHAL ; 
 struct milenage_parameters* get_milenage (char*) ; 
 int /*<<< orphan*/  gsm_milenage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ *,int) ; 
 int os_snprintf (char*,int,char*,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 char* os_strchr (char*,char) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gsm_auth_req(char *imsi, char *resp, size_t resp_len)
{
	int count, ret;
	char *pos, *rpos, *rend;
	struct milenage_parameters *m;

	resp[0] = '\0';

	pos = os_strchr(imsi, ' ');
	if (!pos)
		return -1;
	*pos++ = '\0';

	rend = resp + resp_len;
	rpos = resp;
	ret = os_snprintf(rpos, rend - rpos, "GSM-AUTH-RESP %s", imsi);
	if (os_snprintf_error(rend - rpos, ret))
		return -1;
	rpos += ret;

	m = get_milenage(imsi);
	if (m) {
		u8 _rand[16], sres[4], kc[8];
		for (count = 0; count < EAP_SIM_MAX_CHAL; count++) {
			if (hexstr2bin(pos, _rand, 16) != 0)
				return -1;
			gsm_milenage(m->opc, m->ki, _rand, sres, kc);
			*rpos++ = count == 0 ? ' ' : ':';
			rpos += wpa_snprintf_hex(rpos, rend - rpos, kc, 8);
			*rpos++ = ':';
			rpos += wpa_snprintf_hex(rpos, rend - rpos, sres, 4);
			pos += 16 * 2;
			if (*pos != ':')
				break;
			pos++;
		}
		*rpos = '\0';
		return 0;
	}

	printf("No GSM triplets found for %s\n", imsi);
	ret = os_snprintf(rpos, rend - rpos, " FAILURE");
	if (os_snprintf_error(rend - rpos, ret))
		return -1;
	rpos += ret;

	return 0;
}