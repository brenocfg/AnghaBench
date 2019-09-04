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

void test_core_iconv__decomposed_to_precomposed(void)
{
#ifdef GIT_USE_ICONV
	const char *data = nfd;
	size_t datalen, nfdlen = strlen(nfd);

	datalen = nfdlen;
	cl_git_pass(git_path_iconv(&ic, &data, &datalen));
	GIT_UNUSED(datalen);

	/* The decomposed nfd string should be transformed to the nfc form
	 * (on platforms where iconv is enabled, of course).
	 */
	cl_assert_equal_s(nfc, data);

	/* should be able to do it multiple times with the same git_path_iconv_t */
	data = nfd; datalen = nfdlen;
	cl_git_pass(git_path_iconv(&ic, &data, &datalen));
	cl_assert_equal_s(nfc, data);

	data = nfd; datalen = nfdlen;
	cl_git_pass(git_path_iconv(&ic, &data, &datalen));
	cl_assert_equal_s(nfc, data);
#endif
}