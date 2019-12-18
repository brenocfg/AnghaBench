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
struct stat {int dummy; } ;
struct index_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ sd_size; } ;
struct cache_entry {TYPE_1__ ce_stat_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ce_match_stat_basic (struct cache_entry*,struct stat*) ; 
 scalar_t__ ce_modified_check_fs (struct index_state*,struct cache_entry*,struct stat*) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void ce_smudge_racily_clean_entry(struct index_state *istate,
					 struct cache_entry *ce)
{
	/*
	 * The only thing we care about in this function is to smudge the
	 * falsely clean entry due to touch-update-touch race, so we leave
	 * everything else as they are.  We are called for entries whose
	 * ce_stat_data.sd_mtime match the index file mtime.
	 *
	 * Note that this actually does not do much for gitlinks, for
	 * which ce_match_stat_basic() always goes to the actual
	 * contents.  The caller checks with is_racy_timestamp() which
	 * always says "no" for gitlinks, so we are not called for them ;-)
	 */
	struct stat st;

	if (lstat(ce->name, &st) < 0)
		return;
	if (ce_match_stat_basic(ce, &st))
		return;
	if (ce_modified_check_fs(istate, ce, &st)) {
		/* This is "racily clean"; smudge it.  Note that this
		 * is a tricky code.  At first glance, it may appear
		 * that it can break with this sequence:
		 *
		 * $ echo xyzzy >frotz
		 * $ git-update-index --add frotz
		 * $ : >frotz
		 * $ sleep 3
		 * $ echo filfre >nitfol
		 * $ git-update-index --add nitfol
		 *
		 * but it does not.  When the second update-index runs,
		 * it notices that the entry "frotz" has the same timestamp
		 * as index, and if we were to smudge it by resetting its
		 * size to zero here, then the object name recorded
		 * in index is the 6-byte file but the cached stat information
		 * becomes zero --- which would then match what we would
		 * obtain from the filesystem next time we stat("frotz").
		 *
		 * However, the second update-index, before calling
		 * this function, notices that the cached size is 6
		 * bytes and what is on the filesystem is an empty
		 * file, and never calls us, so the cached size information
		 * for "frotz" stays 6 which does not match the filesystem.
		 */
		ce->ce_stat_data.sd_size = 0;
	}
}