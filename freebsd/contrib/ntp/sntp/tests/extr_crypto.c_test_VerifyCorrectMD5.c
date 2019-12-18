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
 int /*<<< orphan*/  MD5_LENGTH ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_md5 (char const*,int const,int /*<<< orphan*/ ,struct key*) ; 
 int /*<<< orphan*/  keytype_from_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

void
test_VerifyCorrectMD5(void)
{
	const char* PKT_DATA =
	    "sometestdata"			/* Data */
	    "\0\0\0\0"				/* Key-ID (unused) */
	    "\xc7\x58\x99\xdd\x99\x32\x0f\x71"	/* MAC */
	    "\x2b\x7b\xfe\x4f\xa2\x32\xcf\xac";
	const int PKT_LEN = 12;

	struct key md5;
	md5.next = NULL;
	md5.key_id = 0;
	md5.key_len = 6;
	memcpy(&md5.key_seq, "md5key", md5.key_len);
	strlcpy(md5.typen, "MD5", sizeof(md5.typen));
	md5.typei = keytype_from_text(md5.typen, NULL);

	TEST_ASSERT_TRUE(auth_md5(PKT_DATA, PKT_LEN, MD5_LENGTH, &md5));
}