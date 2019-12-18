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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  hashsig_in_progress ;
typedef  int /*<<< orphan*/  git_hashsig_option_t ;
typedef  int /*<<< orphan*/  git_hashsig ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_futils_open_ro (char const*) ; 
 int /*<<< orphan*/  git_hashsig_free (int /*<<< orphan*/ *) ; 
 int hashsig_add_hashes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hashsig_alloc (int /*<<< orphan*/ ) ; 
 int hashsig_finalize_hashes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashsig_in_progress_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_close (int) ; 
 scalar_t__ p_read (int,int /*<<< orphan*/ *,int) ; 

int git_hashsig_create_fromfile(
	git_hashsig **out,
	const char *path,
	git_hashsig_option_t opts)
{
	uint8_t buf[0x1000];
	ssize_t buflen = 0;
	int error = 0, fd;
	hashsig_in_progress prog;
	git_hashsig *sig = hashsig_alloc(opts);
	GIT_ERROR_CHECK_ALLOC(sig);

	if ((fd = git_futils_open_ro(path)) < 0) {
		git__free(sig);
		return fd;
	}

	hashsig_in_progress_init(&prog, sig);

	while (!error) {
		if ((buflen = p_read(fd, buf, sizeof(buf))) <= 0) {
			if ((error = (int)buflen) < 0)
				git_error_set(GIT_ERROR_OS,
					"read error on '%s' calculating similarity hashes", path);
			break;
		}

		error = hashsig_add_hashes(sig, buf, buflen, &prog);
	}

	p_close(fd);

	if (!error)
		error = hashsig_finalize_hashes(sig);

	if (!error)
		*out = sig;
	else
		git_hashsig_free(sig);

	return error;
}