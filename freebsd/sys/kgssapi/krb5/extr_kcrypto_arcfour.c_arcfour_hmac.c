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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
arcfour_hmac(uint8_t *key, uint8_t *data, size_t datalen,
	uint8_t *result)
{
	uint8_t buf[64];
	MD5_CTX md5;
	int i;

	for (i = 0; i < 16; i++)
		buf[i] = key[i] ^ 0x36;
	for (; i < 64; i++)
		buf[i] = 0x36;

	MD5Init(&md5);
	MD5Update(&md5, buf, 64);
	MD5Update(&md5, data, datalen);
	MD5Final(result, &md5);

	for (i = 0; i < 16; i++)
		buf[i] = key[i] ^ 0x5c;
	for (; i < 64; i++)
		buf[i] = 0x5c;
	
	MD5Init(&md5);
	MD5Update(&md5, buf, 64);
	MD5Update(&md5, result, 16);
	MD5Final(result, &md5);
}