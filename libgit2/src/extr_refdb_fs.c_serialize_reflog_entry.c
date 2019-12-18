#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_9__ {int size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_signature__writebuf (TYPE_1__*,char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int serialize_reflog_entry(
	git_buf *buf,
	const git_oid *oid_old,
	const git_oid *oid_new,
	const git_signature *committer,
	const char *msg)
{
	char raw_old[GIT_OID_HEXSZ+1];
	char raw_new[GIT_OID_HEXSZ+1];

	git_oid_tostr(raw_old, GIT_OID_HEXSZ+1, oid_old);
	git_oid_tostr(raw_new, GIT_OID_HEXSZ+1, oid_new);

	git_buf_clear(buf);

	git_buf_puts(buf, raw_old);
	git_buf_putc(buf, ' ');
	git_buf_puts(buf, raw_new);

	git_signature__writebuf(buf, " ", committer);

	/* drop trailing LF */
	git_buf_rtrim(buf);

	if (msg) {
		size_t i;

		git_buf_putc(buf, '\t');
		git_buf_puts(buf, msg);

		for (i = 0; i < buf->size - 2; i++)
			if (buf->ptr[i] == '\n')
				buf->ptr[i] = ' ';
		git_buf_rtrim(buf);
	}

	git_buf_putc(buf, '\n');

	return git_buf_oom(buf);
}