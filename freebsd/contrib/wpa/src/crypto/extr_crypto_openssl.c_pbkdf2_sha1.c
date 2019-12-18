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
 int PKCS5_PBKDF2_HMAC_SHA1 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 

int pbkdf2_sha1(const char *passphrase, const u8 *ssid, size_t ssid_len,
		int iterations, u8 *buf, size_t buflen)
{
	if (PKCS5_PBKDF2_HMAC_SHA1(passphrase, os_strlen(passphrase), ssid,
				   ssid_len, iterations, buflen, buf) != 1)
		return -1;
	return 0;
}