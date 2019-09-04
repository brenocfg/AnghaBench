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
struct untracked_cache_dir {int dummy; } ;
struct strbuf {char* buf; scalar_t__ len; } ;
struct index_state {int dummy; } ;
struct dir_struct {TYPE_1__* untracked; } ;
struct cached_dir {int /*<<< orphan*/  fdir; struct untracked_cache_dir* untracked; } ;
struct TYPE_2__ {int /*<<< orphan*/  dir_opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  invalidate_directory (TYPE_1__*,struct untracked_cache_dir*) ; 
 int /*<<< orphan*/  memset (struct cached_dir*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opendir (char const*) ; 
 scalar_t__ valid_cached_dir (struct dir_struct*,struct untracked_cache_dir*,struct index_state*,struct strbuf*,int) ; 
 int /*<<< orphan*/  warning_errno (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int open_cached_dir(struct cached_dir *cdir,
			   struct dir_struct *dir,
			   struct untracked_cache_dir *untracked,
			   struct index_state *istate,
			   struct strbuf *path,
			   int check_only)
{
	const char *c_path;

	memset(cdir, 0, sizeof(*cdir));
	cdir->untracked = untracked;
	if (valid_cached_dir(dir, untracked, istate, path, check_only))
		return 0;
	c_path = path->len ? path->buf : ".";
	cdir->fdir = opendir(c_path);
	if (!cdir->fdir)
		warning_errno(_("could not open directory '%s'"), c_path);
	if (dir->untracked) {
		invalidate_directory(dir->untracked, untracked);
		dir->untracked->dir_opened++;
	}
	if (!cdir->fdir)
		return -1;
	return 0;
}