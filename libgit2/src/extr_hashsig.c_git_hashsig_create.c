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
typedef  int /*<<< orphan*/  hashsig_in_progress ;
typedef  int /*<<< orphan*/  git_hashsig_option_t ;
typedef  int /*<<< orphan*/  git_hashsig ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hashsig_free (int /*<<< orphan*/ *) ; 
 int hashsig_add_hashes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hashsig_alloc (int /*<<< orphan*/ ) ; 
 int hashsig_finalize_hashes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashsig_in_progress_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_hashsig_create(
	git_hashsig **out,
	const char *buf,
	size_t buflen,
	git_hashsig_option_t opts)
{
	int error;
	hashsig_in_progress prog;
	git_hashsig *sig = hashsig_alloc(opts);
	GIT_ERROR_CHECK_ALLOC(sig);

	hashsig_in_progress_init(&prog, sig);

	error = hashsig_add_hashes(sig, (const uint8_t *)buf, buflen, &prog);

	if (!error)
		error = hashsig_finalize_hashes(sig);

	if (!error)
		*out = sig;
	else
		git_hashsig_free(sig);

	return error;
}