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

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_iconv (int /*<<< orphan*/ *,char const**,size_t*) ; 
 int /*<<< orphan*/  ic ; 
 char* nfc ; 
 size_t strlen (char*) ; 

void test_core_iconv__precomposed_is_unmodified(void)
{
#ifdef GIT_USE_ICONV
	const char *data = nfc;
	size_t datalen = strlen(nfc);

	cl_git_pass(git_path_iconv(&ic, &data, &datalen));
	GIT_UNUSED(datalen);

	/* data is already in precomposed form, so even though some bytes have
	 * the high-bit set, the iconv transform should result in no change.
	 */
	cl_assert_equal_s(nfc, data);
#endif
}