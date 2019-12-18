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
struct key {int /*<<< orphan*/  typen; scalar_t__ key_len; int /*<<< orphan*/  key_seq; scalar_t__ key_id; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 char* CMAC ; 
 scalar_t__ CMAC_LENGTH ; 
 int /*<<< orphan*/  VerifyLocalCMAC (struct key*) ; 
 int /*<<< orphan*/  VerifyOpenSSLCMAC (struct key*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

void
test_VerifyCMAC(void)
{
	const char* PKT_DATA =
	    "sometestdata"				/* Data */
	    "\0\0\0\0"					/* Key-ID (unused) */
	    "\x4e\x0c\xf0\xe2\xc7\x8e\xbb\xbf"		/* MAC */
	    "\x79\xfc\x87\xc7\x8b\xb7\x4a\x0b";
	const int PKT_LEN = 12;
	struct key cmac;

	cmac.next = NULL;
	cmac.key_id = 0;
	cmac.key_len = CMAC_LENGTH;
	memcpy(&cmac.key_seq, "aes-128-cmac-key", cmac.key_len);
	memcpy(&cmac.typen, CMAC, strlen(CMAC) + 1);

	VerifyOpenSSLCMAC(&cmac);
	VerifyLocalCMAC(&cmac);
}