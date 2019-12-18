#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;
typedef  int /*<<< orphan*/  git_refdb_backend ;
typedef  int /*<<< orphan*/  git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int refdb_fs_backend__delete_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int refdb_fs_backend__write_tail (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*) ; 

__attribute__((used)) static int refdb_fs_backend__unlock(git_refdb_backend *backend, void *payload, int success, int update_reflog,
				    const git_reference *ref, const git_signature *sig, const char *message)
{
	git_filebuf *lock = (git_filebuf *) payload;
	int error = 0;

	if (success == 2)
		error = refdb_fs_backend__delete_tail(backend, lock, ref->name, NULL, NULL);
	else if (success)
		error = refdb_fs_backend__write_tail(backend, ref, lock, update_reflog, NULL, NULL, sig, message);
	else
		git_filebuf_cleanup(lock);

	git__free(lock);
	return error;
}