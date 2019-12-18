#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  st_mode; } ;
struct dir_iterator {int /*<<< orphan*/  relative_path; TYPE_1__ st; } ;

/* Variables and functions */
 unsigned int DIR_ITERATOR_FOLLOW_SYMLINKS ; 
 unsigned int DIR_ITERATOR_PEDANTIC ; 
 scalar_t__ ENOENT ; 
 int ITER_DONE ; 
 int ITER_OK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  copy_alternates (struct strbuf*,char const*) ; 
 scalar_t__ copy_file_with_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dir_iterator_advance (struct dir_iterator*) ; 
 struct dir_iterator* dir_iterator_begin (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fspathcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkdir_if_missing (int /*<<< orphan*/ ,int) ; 
 scalar_t__ option_local ; 
 int option_no_hardlinks ; 
 int /*<<< orphan*/  real_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_or_link_directory(struct strbuf *src, struct strbuf *dest,
				   const char *src_repo)
{
	int src_len, dest_len;
	struct dir_iterator *iter;
	int iter_status;
	unsigned int flags;

	mkdir_if_missing(dest->buf, 0777);

	flags = DIR_ITERATOR_PEDANTIC | DIR_ITERATOR_FOLLOW_SYMLINKS;
	iter = dir_iterator_begin(src->buf, flags);

	if (!iter)
		die_errno(_("failed to start iterator over '%s'"), src->buf);

	strbuf_addch(src, '/');
	src_len = src->len;
	strbuf_addch(dest, '/');
	dest_len = dest->len;

	while ((iter_status = dir_iterator_advance(iter)) == ITER_OK) {
		strbuf_setlen(src, src_len);
		strbuf_addstr(src, iter->relative_path);
		strbuf_setlen(dest, dest_len);
		strbuf_addstr(dest, iter->relative_path);

		if (S_ISDIR(iter->st.st_mode)) {
			mkdir_if_missing(dest->buf, 0777);
			continue;
		}

		/* Files that cannot be copied bit-for-bit... */
		if (!fspathcmp(iter->relative_path, "info/alternates")) {
			copy_alternates(src, src_repo);
			continue;
		}

		if (unlink(dest->buf) && errno != ENOENT)
			die_errno(_("failed to unlink '%s'"), dest->buf);
		if (!option_no_hardlinks) {
			if (!link(real_path(src->buf), dest->buf))
				continue;
			if (option_local > 0)
				die_errno(_("failed to create link '%s'"), dest->buf);
			option_no_hardlinks = 1;
		}
		if (copy_file_with_time(dest->buf, src->buf, 0666))
			die_errno(_("failed to copy file to '%s'"), dest->buf);
	}

	if (iter_status != ITER_DONE) {
		strbuf_setlen(src, src_len);
		die(_("failed to iterate over '%s'"), src->buf);
	}
}