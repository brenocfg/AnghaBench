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
typedef  int /*<<< orphan*/  send_start_key ;
typedef  int /*<<< orphan*/  password_hash_hash ;
typedef  int /*<<< orphan*/  password_hash ;
typedef  int /*<<< orphan*/  nt_response ;
typedef  int /*<<< orphan*/  master_key ;
typedef  int /*<<< orphan*/  authenticator_response ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ generate_authenticator_response (int*,int /*<<< orphan*/ ,int*,int*,int*,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ generate_nt_response (int*,int*,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ get_asymetric_start_key (int*,int*,int,int,int) ; 
 scalar_t__ get_master_key (int*,int*,int*) ; 
 scalar_t__ hash_nt_password_hash (int*,int*) ; 
 scalar_t__ nt_password_hash (int*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ os_memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int test_ms_funcs(void)
{
#ifndef CONFIG_FIPS
	/* Test vector from RFC2759 example */
	char *username = "User";
	char *password = "clientPass";
	u8 auth_challenge[] = {
		0x5B, 0x5D, 0x7C, 0x7D, 0x7B, 0x3F, 0x2F, 0x3E,
		0x3C, 0x2C, 0x60, 0x21, 0x32, 0x26, 0x26, 0x28
	};
	u8 peer_challenge[] = {
		0x21, 0x40, 0x23, 0x24, 0x25, 0x5E, 0x26, 0x2A,
		0x28, 0x29, 0x5F, 0x2B, 0x3A, 0x33, 0x7C, 0x7E
	};
	u8 password_hash[] = {
		0x44, 0xEB, 0xBA, 0x8D, 0x53, 0x12, 0xB8, 0xD6,
		0x11, 0x47, 0x44, 0x11, 0xF5, 0x69, 0x89, 0xAE
	};
	u8 nt_response[] = {
		0x82, 0x30, 0x9E, 0xCD, 0x8D, 0x70, 0x8B, 0x5E,
		0xA0, 0x8F, 0xAA, 0x39, 0x81, 0xCD, 0x83, 0x54,
		0x42, 0x33, 0x11, 0x4A, 0x3D, 0x85, 0xD6, 0xDF
	};
	u8 password_hash_hash[] = {
		0x41, 0xC0, 0x0C, 0x58, 0x4B, 0xD2, 0xD9, 0x1C,
		0x40, 0x17, 0xA2, 0xA1, 0x2F, 0xA5, 0x9F, 0x3F
	};
	u8 authenticator_response[] = {
		0x40, 0x7A, 0x55, 0x89, 0x11, 0x5F, 0xD0, 0xD6,
		0x20, 0x9F, 0x51, 0x0F, 0xE9, 0xC0, 0x45, 0x66,
		0x93, 0x2C, 0xDA, 0x56
	};
	u8 master_key[] = {
		0xFD, 0xEC, 0xE3, 0x71, 0x7A, 0x8C, 0x83, 0x8C,
		0xB3, 0x88, 0xE5, 0x27, 0xAE, 0x3C, 0xDD, 0x31
	};
	u8 send_start_key[] = {
		0x8B, 0x7C, 0xDC, 0x14, 0x9B, 0x99, 0x3A, 0x1B,
		0xA1, 0x18, 0xCB, 0x15, 0x3F, 0x56, 0xDC, 0xCB
	};
	u8 buf[32];
	int errors = 0;

	if (nt_password_hash((u8 *) password, os_strlen(password), buf) ||
	    os_memcmp(password_hash, buf, sizeof(password_hash)) != 0) {
		wpa_printf(MSG_ERROR, "nt_password_hash failed");
		errors++;
	}

	if (generate_nt_response(auth_challenge, peer_challenge,
				 (u8 *) username, os_strlen(username),
				 (u8 *) password, os_strlen(password), buf) ||
	    os_memcmp(nt_response, buf, sizeof(nt_response)) != 0) {
		wpa_printf(MSG_ERROR, "generate_nt_response failed");
		errors++;
	}

	if (hash_nt_password_hash(password_hash, buf) ||
	    os_memcmp(password_hash_hash, buf,
		      sizeof(password_hash_hash)) != 0) {
		wpa_printf(MSG_ERROR, "hash_nt_password_hash failed");
		errors++;
	}

	if (generate_authenticator_response((u8 *) password,
					    os_strlen(password),
					    peer_challenge, auth_challenge,
					    (u8 *) username,
					    os_strlen(username),
					    nt_response, buf) ||
	    os_memcmp(authenticator_response, buf,
		      sizeof(authenticator_response)) != 0) {
		wpa_printf(MSG_ERROR, "generate_authenticator_response failed");
		errors++;
	}

	if (get_master_key(password_hash_hash, nt_response, buf) ||
	    os_memcmp(master_key, buf, sizeof(master_key)) != 0) {
		wpa_printf(MSG_ERROR, "get_master_key failed");
		errors++;
	}

	if (get_asymetric_start_key(master_key, buf, sizeof(send_start_key),
				    1, 1) ||
	    os_memcmp(send_start_key, buf, sizeof(send_start_key)) != 0) {
		wpa_printf(MSG_ERROR, "get_asymetric_start_key failed");
		errors++;
	}

	if (errors)
		wpa_printf(MSG_ERROR, "ms_funcs: %d errors", errors);
	else
		wpa_printf(MSG_INFO, "ms_funcs test cases passed");

	return errors;
#else /* CONFIG_FIPS */
	wpa_printf(MSG_INFO, "ms_funcs test cases skipped due to CONFIG_FIPS");
	return 0;
#endif /* CONFIG_FIPS */
}