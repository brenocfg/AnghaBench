#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  sd_size; } ;
struct cache_entry {int ce_flags; int ce_mode; TYPE_1__ oid; TYPE_2__ ce_stat_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 int CE_REMOVE ; 
 int DATA_CHANGED ; 
 int MODE_CHANGED ; 
#define  S_IFGITLINK 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  S_ISDIR (int) ; 
 int /*<<< orphan*/  S_ISLNK (int) ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int TYPE_CHANGED ; 
 int /*<<< orphan*/  ce_compare_gitlink (struct cache_entry const*) ; 
 int /*<<< orphan*/  has_symlinks ; 
 int /*<<< orphan*/  is_empty_blob_sha1 (int /*<<< orphan*/ ) ; 
 unsigned int match_stat_data (TYPE_2__*,struct stat*) ; 
 int /*<<< orphan*/  trust_executable_bit ; 

__attribute__((used)) static int ce_match_stat_basic(const struct cache_entry *ce, struct stat *st)
{
	unsigned int changed = 0;

	if (ce->ce_flags & CE_REMOVE)
		return MODE_CHANGED | DATA_CHANGED | TYPE_CHANGED;

	switch (ce->ce_mode & S_IFMT) {
	case S_IFREG:
		changed |= !S_ISREG(st->st_mode) ? TYPE_CHANGED : 0;
		/* We consider only the owner x bit to be relevant for
		 * "mode changes"
		 */
		if (trust_executable_bit &&
		    (0100 & (ce->ce_mode ^ st->st_mode)))
			changed |= MODE_CHANGED;
		break;
	case S_IFLNK:
		if (!S_ISLNK(st->st_mode) &&
		    (has_symlinks || !S_ISREG(st->st_mode)))
			changed |= TYPE_CHANGED;
		break;
	case S_IFGITLINK:
		/* We ignore most of the st_xxx fields for gitlinks */
		if (!S_ISDIR(st->st_mode))
			changed |= TYPE_CHANGED;
		else if (ce_compare_gitlink(ce))
			changed |= DATA_CHANGED;
		return changed;
	default:
		BUG("unsupported ce_mode: %o", ce->ce_mode);
	}

	changed |= match_stat_data(&ce->ce_stat_data, st);

	/* Racily smudged entry? */
	if (!ce->ce_stat_data.sd_size) {
		if (!is_empty_blob_sha1(ce->oid.hash))
			changed |= DATA_CHANGED;
	}

	return changed;
}