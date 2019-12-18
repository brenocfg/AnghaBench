#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {char* ptr; size_t size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 size_t GIT_OID_HEXSZ ; 
 scalar_t__ git__fromhex (char) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 size_t git_buf_len (TYPE_1__*) ; 
 int git_buf_puts (TYPE_1__*,char const*) ; 
 int git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int process_entry_path(
	const char* entry_path,
	git_oid *annotated_object_id)
{
	int error = 0;
	size_t i = 0, j = 0, len;
	git_buf buf = GIT_BUF_INIT;

	if ((error = git_buf_puts(&buf, entry_path)) < 0)
		goto cleanup;

	len = git_buf_len(&buf);

	while (i < len) {
		if (buf.ptr[i] == '/') {
			i++;
			continue;
		}

		if (git__fromhex(buf.ptr[i]) < 0) {
			/* This is not a note entry */
			goto cleanup;
		}

		if (i != j)
			buf.ptr[j] = buf.ptr[i];

		i++;
		j++;
	}

	buf.ptr[j] = '\0';
	buf.size = j;

	if (j != GIT_OID_HEXSZ) {
		/* This is not a note entry */
		goto cleanup;
	}

	error = git_oid_fromstr(annotated_object_id, buf.ptr);

cleanup:
	git_buf_dispose(&buf);
	return error;
}