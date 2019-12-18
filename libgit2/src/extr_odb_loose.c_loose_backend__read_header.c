#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  loose_backend ;
struct TYPE_3__ {size_t len; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_object_t ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_INVALID ; 
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_odb__error_notfound (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ locate_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int read_header_loose (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loose_backend__read_header(size_t *len_p, git_object_t *type_p, git_odb_backend *backend, const git_oid *oid)
{
	git_buf object_path = GIT_BUF_INIT;
	git_rawobj raw;
	int error;

	assert(backend && oid);

	raw.len = 0;
	raw.type = GIT_OBJECT_INVALID;

	if (locate_object(&object_path, (loose_backend *)backend, oid) < 0) {
		error = git_odb__error_notfound("no matching loose object",
			oid, GIT_OID_HEXSZ);
	} else if ((error = read_header_loose(&raw, &object_path)) == 0) {
		*len_p = raw.len;
		*type_p = raw.type;
	}

	git_buf_dispose(&object_path);

	return error;
}