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
struct stat {int dummy; } ;
struct index_state {int dummy; } ;
struct diff_filespec {int /*<<< orphan*/  oid; int /*<<< orphan*/  path; scalar_t__ is_stdin; int /*<<< orphan*/  oid_valid; } ;

/* Variables and functions */
 scalar_t__ DIFF_FILE_VALID (struct diff_filespec*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ index_path (struct index_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void diff_fill_oid_info(struct diff_filespec *one, struct index_state *istate)
{
	if (DIFF_FILE_VALID(one)) {
		if (!one->oid_valid) {
			struct stat st;
			if (one->is_stdin) {
				oidclr(&one->oid);
				return;
			}
			if (lstat(one->path, &st) < 0)
				die_errno("stat '%s'", one->path);
			if (index_path(istate, &one->oid, one->path, &st, 0))
				die("cannot hash %s", one->path);
		}
	}
	else
		oidclr(&one->oid);
}