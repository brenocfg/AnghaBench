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
struct scard_data {scalar_t__ sim_type; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 long SCARD_S_SUCCESS ; 
 scalar_t__ SCARD_USIM ; 
 unsigned char SIM_CMD_READ_RECORD ; 
 unsigned char USIM_CLA ; 
 long scard_transmit (struct scard_data*,unsigned char*,int,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int scard_get_record_len(struct scard_data *scard, unsigned char recnum,
				unsigned char mode)
{
	unsigned char buf[255];
	unsigned char cmd[5] = { SIM_CMD_READ_RECORD /* , len */ };
	size_t blen;
	long ret;

	if (scard->sim_type == SCARD_USIM)
		cmd[0] = USIM_CLA;
	cmd[2] = recnum;
	cmd[3] = mode;
	cmd[4] = sizeof(buf);

	blen = sizeof(buf);
	ret = scard_transmit(scard, cmd, sizeof(cmd), buf, &blen);
	if (ret != SCARD_S_SUCCESS) {
		wpa_printf(MSG_DEBUG, "SCARD: failed to determine file "
			   "length for record %d", recnum);
		return -1;
	}

	wpa_hexdump(MSG_DEBUG, "SCARD: file length determination response",
		    buf, blen);

	if (blen < 2 || (buf[0] != 0x6c && buf[0] != 0x67)) {
		wpa_printf(MSG_DEBUG, "SCARD: unexpected response to file "
			   "length determination");
		return -1;
	}

	return buf[1];
}