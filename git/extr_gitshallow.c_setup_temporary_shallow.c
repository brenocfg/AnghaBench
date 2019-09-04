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
struct tempfile {int /*<<< orphan*/  fd; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct oid_array {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ close_tempfile_gently (struct tempfile*) ; 
 int /*<<< orphan*/  die_errno (char*,char const*) ; 
 char const* get_tempfile_path (struct tempfile*) ; 
 int /*<<< orphan*/  git_path (char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ write_in_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_shallow_commits (struct strbuf*,int /*<<< orphan*/ ,struct oid_array const*) ; 
 struct tempfile* xmks_tempfile (int /*<<< orphan*/ ) ; 

const char *setup_temporary_shallow(const struct oid_array *extra)
{
	struct tempfile *temp;
	struct strbuf sb = STRBUF_INIT;

	if (write_shallow_commits(&sb, 0, extra)) {
		temp = xmks_tempfile(git_path("shallow_XXXXXX"));

		if (write_in_full(temp->fd, sb.buf, sb.len) < 0 ||
		    close_tempfile_gently(temp) < 0)
			die_errno("failed to write to %s",
				  get_tempfile_path(temp));
		strbuf_release(&sb);
		return get_tempfile_path(temp);
	}
	/*
	 * is_repository_shallow() sees empty string as "no shallow
	 * file".
	 */
	return "";
}