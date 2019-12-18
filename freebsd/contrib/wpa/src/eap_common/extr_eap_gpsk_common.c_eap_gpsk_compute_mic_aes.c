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
 int /*<<< orphan*/  MSG_DEBUG ; 
 int omac1_aes_128 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static int eap_gpsk_compute_mic_aes(const u8 *sk, size_t sk_len,
				    const u8 *data, size_t len, u8 *mic)
{
	if (sk_len != 16) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Invalid SK length %lu for "
			   "AES-CMAC MIC", (unsigned long) sk_len);
		return -1;
	}

	return omac1_aes_128(sk, data, len, mic);
}