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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_array_oid_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git_array_get (int /*<<< orphan*/ ,size_t) ; 
 size_t git_array_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 scalar_t__ git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_oid__writebuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_signature__writebuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int git_commit__create_buffer_internal(
	git_buf *out,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message,
	const git_oid *tree,
	git_array_oid_t *parents)
{
	size_t i = 0;
	const git_oid *parent;

	assert(out && tree);

	git_oid__writebuf(out, "tree ", tree);

	for (i = 0; i < git_array_size(*parents); i++) {
		parent = git_array_get(*parents, i);
		git_oid__writebuf(out, "parent ", parent);
	}

	git_signature__writebuf(out, "author ", author);
	git_signature__writebuf(out, "committer ", committer);

	if (message_encoding != NULL)
		git_buf_printf(out, "encoding %s\n", message_encoding);

	git_buf_putc(out, '\n');

	if (git_buf_puts(out, message) < 0)
		goto on_error;

	return 0;

on_error:
	git_buf_dispose(out);
	return -1;
}