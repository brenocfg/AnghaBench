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

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int omac1_aes_128 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int omac1_aes_256 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int ieee802_1x_icv_aes_cmac(const u8 *ick, size_t ick_bytes, const u8 *msg,
			    size_t msg_bytes, u8 *icv)
{
	int res;

	if (ick_bytes == 16)
		res = omac1_aes_128(ick, msg, msg_bytes, icv);
	else if (ick_bytes == 32)
		res = omac1_aes_256(ick, msg, msg_bytes, icv);
	else
		return -1;
	if (res) {
		wpa_printf(MSG_ERROR,
			   "MKA: AES-CMAC failed for ICV calculation");
		return -1;
	}
	return 0;
}