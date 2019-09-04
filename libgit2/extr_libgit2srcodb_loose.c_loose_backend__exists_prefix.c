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
typedef  int /*<<< orphan*/  loose_backend ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 size_t GIT_OID_MINPREFIXLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int locate_object_short_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int loose_backend__exists_prefix(
	git_oid *out, git_odb_backend *backend, const git_oid *short_id, size_t len)
{
	git_buf object_path = GIT_BUF_INIT;
	int error;

	assert(backend && out && short_id && len >= GIT_OID_MINPREFIXLEN);

	error = locate_object_short_oid(
		&object_path, out, (loose_backend *)backend, short_id, len);

	git_buf_dispose(&object_path);

	return error;
}