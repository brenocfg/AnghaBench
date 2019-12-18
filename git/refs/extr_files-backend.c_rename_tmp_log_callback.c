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
struct rename_cb {scalar_t__ true_errno; int /*<<< orphan*/  tmp_renamed_log; } ;

/* Variables and functions */
 scalar_t__ EISDIR ; 
 scalar_t__ ENOTDIR ; 
 scalar_t__ errno ; 
 scalar_t__ rename (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int rename_tmp_log_callback(const char *path, void *cb_data)
{
	struct rename_cb *cb = cb_data;

	if (rename(cb->tmp_renamed_log, path)) {
		/*
		 * rename(a, b) when b is an existing directory ought
		 * to result in ISDIR, but Solaris 5.8 gives ENOTDIR.
		 * Sheesh. Record the true errno for error reporting,
		 * but report EISDIR to raceproof_create_file() so
		 * that it knows to retry.
		 */
		cb->true_errno = errno;
		if (errno == ENOTDIR)
			errno = EISDIR;
		return -1;
	} else {
		return 0;
	}
}