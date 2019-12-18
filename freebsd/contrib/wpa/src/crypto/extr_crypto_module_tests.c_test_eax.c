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
typedef  int /*<<< orphan*/  nonce ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ aes_128_eax_decrypt (int*,int*,int,int*,int,int*,int,int*) ; 
 scalar_t__ aes_128_eax_encrypt (int*,int*,int,int*,int,int*,int,int*) ; 
 scalar_t__ os_memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int test_eax(void)
{
#ifdef EAP_PSK
	u8 msg[] = { 0xF7, 0xFB };
	u8 key[] = { 0x91, 0x94, 0x5D, 0x3F, 0x4D, 0xCB, 0xEE, 0x0B,
		     0xF4, 0x5E, 0xF5, 0x22, 0x55, 0xF0, 0x95, 0xA4 };
	u8 nonce[] = { 0xBE, 0xCA, 0xF0, 0x43, 0xB0, 0xA2, 0x3D, 0x84,
		       0x31, 0x94, 0xBA, 0x97, 0x2C, 0x66, 0xDE, 0xBD };
	u8 hdr[] = { 0xFA, 0x3B, 0xFD, 0x48, 0x06, 0xEB, 0x53, 0xFA };
	u8 cipher[] = { 0x19, 0xDD, 0x5C, 0x4C, 0x93, 0x31, 0x04, 0x9D,
			0x0B, 0xDA, 0xB0, 0x27, 0x74, 0x08, 0xF6, 0x79,
			0x67, 0xE5 };
	u8 data[sizeof(msg)], tag[AES_BLOCK_SIZE];

	os_memcpy(data, msg, sizeof(msg));
	if (aes_128_eax_encrypt(key, nonce, sizeof(nonce), hdr, sizeof(hdr),
				data, sizeof(data), tag)) {
		wpa_printf(MSG_ERROR, "AES-128 EAX mode encryption failed");
		return 1;
	}
	if (os_memcmp(data, cipher, sizeof(data)) != 0) {
		wpa_printf(MSG_ERROR,
			   "AES-128 EAX mode encryption returned invalid cipher text");
		return 1;
	}
	if (os_memcmp(tag, cipher + sizeof(data), AES_BLOCK_SIZE) != 0) {
		wpa_printf(MSG_ERROR,
			   "AES-128 EAX mode encryption returned invalid tag");
		return 1;
	}

	if (aes_128_eax_decrypt(key, nonce, sizeof(nonce), hdr, sizeof(hdr),
				data, sizeof(data), tag)) {
		wpa_printf(MSG_ERROR, "AES-128 EAX mode decryption failed");
		return 1;
	}
	if (os_memcmp(data, msg, sizeof(data)) != 0) {
		wpa_printf(MSG_ERROR,
			   "AES-128 EAX mode decryption returned invalid plain text");
		return 1;
	}

	wpa_printf(MSG_INFO, "AES-128 EAX mode test cases passed");
#endif /* EAP_PSK */

	return 0;
}