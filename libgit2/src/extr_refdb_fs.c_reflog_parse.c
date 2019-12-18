#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {struct TYPE_17__* msg; struct TYPE_17__* committer; int /*<<< orphan*/  oid_cur; int /*<<< orphan*/  oid_old; } ;
typedef  TYPE_1__ git_reflog_entry ;
struct TYPE_18__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ git_reflog ;
struct TYPE_19__ {char* line; size_t line_len; scalar_t__ remain_len; } ;
typedef  TYPE_3__ git_parse_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 TYPE_3__ GIT_PARSE_CTX_INIT ; 
 void* git__calloc (int,int) ; 
 TYPE_1__* git__strndup (char*,size_t) ; 
 int /*<<< orphan*/  git_parse_advance_chars (TYPE_3__*,int) ; 
 scalar_t__ git_parse_advance_expected (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  git_parse_advance_line (TYPE_3__*) ; 
 scalar_t__ git_parse_advance_oid (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ git_parse_ctx_init (TYPE_3__*,char const*,size_t) ; 
 scalar_t__ git_parse_peek (char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry__free (TYPE_1__*) ; 
 scalar_t__ git_signature__parse (TYPE_1__*,char const**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int reflog_parse(git_reflog *log, const char *buf, size_t buf_size)
{
	git_parse_ctx parser = GIT_PARSE_CTX_INIT;

	if ((git_parse_ctx_init(&parser, buf, buf_size)) < 0)
		return -1;

	for (; parser.remain_len; git_parse_advance_line(&parser)) {
		git_reflog_entry *entry;
		const char *sig;
		char c;

		entry = git__calloc(1, sizeof(*entry));
		GIT_ERROR_CHECK_ALLOC(entry);
		entry->committer = git__calloc(1, sizeof(*entry->committer));
		GIT_ERROR_CHECK_ALLOC(entry->committer);

		if (git_parse_advance_oid(&entry->oid_old, &parser) < 0 ||
		    git_parse_advance_expected(&parser, " ", 1) < 0 ||
		    git_parse_advance_oid(&entry->oid_cur, &parser) < 0)
			goto next;

		sig = parser.line;
		while (git_parse_peek(&c, &parser, 0) == 0 && c != '\t' && c != '\n')
			git_parse_advance_chars(&parser, 1);

		if (git_signature__parse(entry->committer, &sig, parser.line, NULL, 0) < 0)
			goto next;

		if (c == '\t') {
			size_t len;
			git_parse_advance_chars(&parser, 1);

			len = parser.line_len;
			if (parser.line[len - 1] == '\n')
				len--;

			entry->msg = git__strndup(parser.line, len);
			GIT_ERROR_CHECK_ALLOC(entry->msg);
		}

		if ((git_vector_insert(&log->entries, entry)) < 0) {
			git_reflog_entry__free(entry);
			return -1;
		}

		continue;

next:
		git_reflog_entry__free(entry);
	}

	return 0;
}