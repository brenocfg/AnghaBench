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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_OK ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expected_commit_content ; 
 int /*<<< orphan*/  git_buf_is_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_set (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

int signing_cb_gpg(
	git_buf *signature,
	git_buf *signature_field,
	const char *commit_content,
	void *payload)
{
	const char *gpg_signature = "-----BEGIN PGP SIGNATURE-----\n\
\n\
iQIzBAEBCgAdFiEEgVlDEfSlmKn0fvGgK++h5T2/ctIFAlwZcrAACgkQK++h5T2/\n\
ctIPVhAA42RyZhMdKl5Bm0KtQco2scsukIg2y7tjSwhti91zDu3HQgpusjjo0fQx\n\
ZzB+OrmlvQ9CDcGpZ0THIzXD8GRJoDMPqdrvZVrBWkGcHvw7/YPA8skzsjkauJ8W\n\
7lzF5LCuHSS6OUmPT/+5hEHPin5PB3zhfszyC+Q7aujnIuPJMrKiMnUa+w1HWifM\n\
km49OOygQ9S6NQoVuEQede22+c76DlDL7yFghGoo1f0sKCE/9LW6SEnwI/bWv9eo\n\
nom5vOPrvQeJiYCQk+2DyWo8RdSxINtY+G9bPE4RXm+6ZgcXECPm9TYDIWpL36fC\n\
jvtGLs98woWFElOziBMp5Tb630GMcSI+q5ivHfJ3WS5NKLYLHBNK4iSFN0/dgAnB\n\
dj6GcKXKWnIBWn6ZM4o40pcM5KSRUUCLtA0ZmjJH4c4zx3X5fUxd+enwkf3e9VZO\n\
fNKC/+xfq6NfoPUPK9+UnchHpJaJw7RG5tZS+sWCz2xpQ1y3/o49xImNyM3wnpvB\n\
cRAZabqIHpZa9/DIUkELOtCzln6niqkjRgg3M/YCCNznwV+0RNgz87VtyTPerdef\n\
xrqn0+ROMF6ebVqIs6PPtuPkxnAJu7TMKXVB5rFnAewS24e6cIGFzeIA7810py3l\n\
cttVRsdOoego+fiy08eFE+aJIeYiINRGhqOBTsuqG4jIdpdKxPE=\n\
=KbsY\n\
-----END PGP SIGNATURE-----";

	cl_assert_equal_b(false, git_buf_is_allocated(signature));
	cl_assert_equal_b(false, git_buf_is_allocated(signature_field));
	cl_assert_equal_s(expected_commit_content, commit_content);
	cl_assert_equal_p(NULL, payload);

	cl_git_pass(git_buf_set(signature, gpg_signature, strlen(gpg_signature) + 1));
	return GIT_OK;
}