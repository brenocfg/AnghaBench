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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 scalar_t__ GIT_OID_HEXSZ ; 
 scalar_t__ git__isspace (char const) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int loose_parse_oid(
	git_oid *oid, const char *filename, git_buf *file_content)
{
	const char *str = git_buf_cstr(file_content);

	if (git_buf_len(file_content) < GIT_OID_HEXSZ)
		goto corrupted;

	/* we need to get 40 OID characters from the file */
	if (git_oid_fromstr(oid, str) < 0)
		goto corrupted;

	/* If the file is longer than 40 chars, the 41st must be a space */
	str += GIT_OID_HEXSZ;
	if (*str == '\0' || git__isspace(*str))
		return 0;

corrupted:
	git_error_set(GIT_ERROR_REFERENCE, "corrupted loose reference file: %s", filename);
	return -1;
}