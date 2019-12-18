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
struct key {int key_len; int /*<<< orphan*/  typen; int /*<<< orphan*/  typei; int /*<<< orphan*/  key_seq; scalar_t__ key_id; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_LENGTH ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_IGNORE_MESSAGE (char*) ; 
 int /*<<< orphan*/  auth_md5 (char const*,int const,int /*<<< orphan*/ ,struct key*) ; 
 int /*<<< orphan*/  keytype_from_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

void
test_VerifySHA1(void)
{
#ifdef OPENSSL

	const char* PKT_DATA =
	    "sometestdata"				/* Data */
	    "\0\0\0\0"					/* Key-ID (unused) */
	    "\xad\x07\xde\x36\x39\xa6\x77\xfa\x5b\xce"	/* MAC */
	    "\x2d\x8a\x7d\x06\x96\xe6\x0c\xbc\xed\xe1";
	const int PKT_LEN = 12;

	struct key sha1;
	sha1.next = NULL;
	sha1.key_id = 0;
	sha1.key_len = 7;
	memcpy(&sha1.key_seq, "sha1key", sha1.key_len);
	strlcpy(sha1.typen, "SHA1", sizeof(sha1.typen));	
	sha1.typei = keytype_from_text(sha1.typen, NULL);

	TEST_ASSERT_TRUE(auth_md5(PKT_DATA, PKT_LEN, SHA1_LENGTH, &sha1));
	
#else
	
	TEST_IGNORE_MESSAGE("OpenSSL not found, skipping...");
	
#endif	/* OPENSSL */
}