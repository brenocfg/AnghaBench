#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  loose_backend ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_backend ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_futils_touch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ object_file_name (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int loose_backend__freshen(
	git_odb_backend *_backend,
	const git_oid *oid)
{
	loose_backend *backend = (loose_backend *)_backend;
	git_buf path = GIT_BUF_INIT;
	int error;

	if (object_file_name(&path, backend, oid) < 0)
		return -1;

	error = git_futils_touch(path.ptr, NULL);
	git_buf_dispose(&path);

	return error;
}