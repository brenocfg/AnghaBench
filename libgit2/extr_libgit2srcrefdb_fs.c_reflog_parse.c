#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_9__ {struct TYPE_9__* msg; struct TYPE_9__* committer; int /*<<< orphan*/  oid_cur; int /*<<< orphan*/  oid_old; } ;
typedef  TYPE_1__ git_reflog_entry ;
struct TYPE_10__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ git_reflog ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int GIT_OID_HEXSZ ; 
 size_t GIT_REFLOG_SIZE_MIN ; 
 void* git__calloc (int,int) ; 
 TYPE_1__* git__strndup (char const*,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_oid_fromstrn (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_reflog_entry__free (TYPE_1__*) ; 
 scalar_t__ git_signature__parse (TYPE_1__*,char const**,char const*,int /*<<< orphan*/ *,char const) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int reflog_parse(git_reflog *log, const char *buf, size_t buf_size)
{
	const char *ptr;
	git_reflog_entry *entry;

#define seek_forward(_increase) do { \
	if (_increase >= buf_size) { \
		git_error_set(GIT_ERROR_INVALID, "ran out of data while parsing reflog"); \
		goto fail; \
	} \
	buf += _increase; \
	buf_size -= _increase; \
	} while (0)

	while (buf_size > GIT_REFLOG_SIZE_MIN) {
		entry = git__calloc(1, sizeof(git_reflog_entry));
		GIT_ERROR_CHECK_ALLOC(entry);

		entry->committer = git__calloc(1, sizeof(git_signature));
		GIT_ERROR_CHECK_ALLOC(entry->committer);

		if (git_oid_fromstrn(&entry->oid_old, buf, GIT_OID_HEXSZ) < 0)
			goto fail;
		seek_forward(GIT_OID_HEXSZ + 1);

		if (git_oid_fromstrn(&entry->oid_cur, buf, GIT_OID_HEXSZ) < 0)
			goto fail;
		seek_forward(GIT_OID_HEXSZ + 1);

		ptr = buf;

		/* Seek forward to the end of the signature. */
		while (*buf && *buf != '\t' && *buf != '\n')
			seek_forward(1);

		if (git_signature__parse(entry->committer, &ptr, buf + 1, NULL, *buf) < 0)
			goto fail;

		if (*buf == '\t') {
			/* We got a message. Read everything till we reach LF. */
			seek_forward(1);
			ptr = buf;

			while (*buf && *buf != '\n')
				seek_forward(1);

			entry->msg = git__strndup(ptr, buf - ptr);
			GIT_ERROR_CHECK_ALLOC(entry->msg);
		} else
			entry->msg = NULL;

		while (*buf && *buf == '\n' && buf_size > 1)
			seek_forward(1);

		if (git_vector_insert(&log->entries, entry) < 0)
			goto fail;
	}

	return 0;

#undef seek_forward

fail:
	git_reflog_entry__free(entry);

	return -1;
}