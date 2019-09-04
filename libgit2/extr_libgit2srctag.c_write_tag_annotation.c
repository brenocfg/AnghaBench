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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_OBJECT ; 
 int /*<<< orphan*/  GIT_OBJECT_TAG ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char) ; 
 scalar_t__ git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_object_type (int /*<<< orphan*/  const*) ; 
 char const* git_object_type2string (int /*<<< orphan*/ ) ; 
 scalar_t__ git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid__writebuf (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature__writebuf (TYPE_1__*,char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int write_tag_annotation(
		git_oid *oid,
		git_repository *repo,
		const char *tag_name,
		const git_object *target,
		const git_signature *tagger,
		const char *message)
{
	git_buf tag = GIT_BUF_INIT;
	git_odb *odb;

	git_oid__writebuf(&tag, "object ", git_object_id(target));
	git_buf_printf(&tag, "type %s\n", git_object_type2string(git_object_type(target)));
	git_buf_printf(&tag, "tag %s\n", tag_name);
	git_signature__writebuf(&tag, "tagger ", tagger);
	git_buf_putc(&tag, '\n');

	if (git_buf_puts(&tag, message) < 0)
		goto on_error;

	if (git_repository_odb__weakptr(&odb, repo) < 0)
		goto on_error;

	if (git_odb_write(oid, odb, tag.ptr, tag.size, GIT_OBJECT_TAG) < 0)
		goto on_error;

	git_buf_dispose(&tag);
	return 0;

on_error:
	git_buf_dispose(&tag);
	git_error_set(GIT_ERROR_OBJECT, "failed to create tag annotation");
	return -1;
}