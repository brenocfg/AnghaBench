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
struct key {int key_id; int key_len; int /*<<< orphan*/  typen; int /*<<< orphan*/  typei; int /*<<< orphan*/  key_seq; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int MD5_LENGTH ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int) ; 
 int /*<<< orphan*/  keytype_from_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_mac (char const*,int const,int,struct key*,char*) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char const*) ; 

void
test_MakeMd5Mac(void)
{
	const char* PKT_DATA = "abcdefgh0123";
	const int PKT_LEN = strlen(PKT_DATA);
	const char* EXPECTED_DIGEST =
		"\x52\x6c\xb8\x38\xaf\x06\x5a\xfb\x6c\x98\xbb\xc0\x9b\x0a\x7a\x1b";
	char actual[MD5_LENGTH];

	struct key md5;
	md5.next = NULL;
	md5.key_id = 10;
	md5.key_len = 6;
	memcpy(&md5.key_seq, "md5seq", md5.key_len);
	strlcpy(md5.typen, "MD5", sizeof(md5.typen));
	md5.typei = keytype_from_text(md5.typen, NULL);
	
	TEST_ASSERT_EQUAL(MD5_LENGTH,
			  make_mac(PKT_DATA, PKT_LEN, MD5_LENGTH, &md5, actual));

	TEST_ASSERT_TRUE(memcmp(EXPECTED_DIGEST, actual, MD5_LENGTH) == 0);
}