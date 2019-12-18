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
struct key {int key_id; int key_len; int /*<<< orphan*/  typen; int /*<<< orphan*/  key_seq; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 char* CMAC ; 
 int CMAC_LENGTH ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_MEMORY (char const*,char*,int) ; 
 int /*<<< orphan*/  TEST_IGNORE_MESSAGE (char*) ; 
 int /*<<< orphan*/  make_mac (char const*,int const,int,struct key*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int strlen (char const*) ; 

void
test_MakeCMac(void)
{
#if defined(OPENSSL) && defined(ENABLE_CMAC)

	const char* PKT_DATA = "abcdefgh0123";
	const int PKT_LEN = strlen(PKT_DATA);
	const char* EXPECTED_DIGEST =
		"\xdd\x35\xd5\xf5\x14\x23\xd9\xd6"
		"\x38\x5d\x29\x80\xfe\x51\xb9\x6b";
	char actual[CMAC_LENGTH];

	struct key cmac;
	cmac.next = NULL;
	cmac.key_id = 30;
	cmac.key_len = CMAC_LENGTH;
	memcpy(&cmac.key_seq, "aes-128-cmac-seq", cmac.key_len);
	memcpy(&cmac.typen, CMAC, strlen(CMAC) + 1);

	TEST_ASSERT_EQUAL(CMAC_LENGTH,
		    make_mac(PKT_DATA, PKT_LEN, CMAC_LENGTH, &cmac, actual));

	TEST_ASSERT_EQUAL_MEMORY(EXPECTED_DIGEST, actual, CMAC_LENGTH);
	
#else
	
	TEST_IGNORE_MESSAGE("OpenSSL not found, skipping...");
	
#endif	/* OPENSSL */
}