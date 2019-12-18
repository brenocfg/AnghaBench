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
struct strbuf {int dummy; } ;
struct stat {int dummy; } ;
struct patch {int dummy; } ;
struct cache_entry {int dummy; } ;
struct apply_state {scalar_t__ check_index; scalar_t__ cached; } ;

/* Variables and functions */
 int SUBMODULE_PATCH_WITHOUT_INDEX ; 
 scalar_t__ S_ISGITLINK (unsigned int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ has_symlink_leading_path (char const*,int /*<<< orphan*/ ) ; 
 int read_file_or_gitlink (struct cache_entry const*,struct strbuf*) ; 
 scalar_t__ read_old_data (struct stat*,struct patch*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int load_patch_target(struct apply_state *state,
			     struct strbuf *buf,
			     const struct cache_entry *ce,
			     struct stat *st,
			     struct patch *patch,
			     const char *name,
			     unsigned expected_mode)
{
	if (state->cached || state->check_index) {
		if (read_file_or_gitlink(ce, buf))
			return error(_("failed to read %s"), name);
	} else if (name) {
		if (S_ISGITLINK(expected_mode)) {
			if (ce)
				return read_file_or_gitlink(ce, buf);
			else
				return SUBMODULE_PATCH_WITHOUT_INDEX;
		} else if (has_symlink_leading_path(name, strlen(name))) {
			return error(_("reading from '%s' beyond a symbolic link"), name);
		} else {
			if (read_old_data(st, patch, name, buf))
				return error(_("failed to read %s"), name);
		}
	}
	return 0;
}