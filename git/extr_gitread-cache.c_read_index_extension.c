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
struct index_state {int /*<<< orphan*/  untracked; int /*<<< orphan*/  resolve_undo; int /*<<< orphan*/  cache_tree; } ;

/* Variables and functions */
 int CACHE_EXT (char const*) ; 
#define  CACHE_EXT_ENDOFINDEXENTRIES 134 
#define  CACHE_EXT_FSMONITOR 133 
#define  CACHE_EXT_INDEXENTRYOFFSETTABLE 132 
#define  CACHE_EXT_LINK 131 
#define  CACHE_EXT_RESOLVE_UNDO 130 
#define  CACHE_EXT_TREE 129 
#define  CACHE_EXT_UNTRACKED 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  cache_tree_read (char const*,unsigned long) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  read_fsmonitor_extension (struct index_state*,char const*,unsigned long) ; 
 int /*<<< orphan*/  read_link_extension (struct index_state*,char const*,unsigned long) ; 
 int /*<<< orphan*/  read_untracked_extension (char const*,unsigned long) ; 
 int /*<<< orphan*/  resolve_undo_read (char const*,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int read_index_extension(struct index_state *istate,
				const char *ext, const char *data, unsigned long sz)
{
	switch (CACHE_EXT(ext)) {
	case CACHE_EXT_TREE:
		istate->cache_tree = cache_tree_read(data, sz);
		break;
	case CACHE_EXT_RESOLVE_UNDO:
		istate->resolve_undo = resolve_undo_read(data, sz);
		break;
	case CACHE_EXT_LINK:
		if (read_link_extension(istate, data, sz))
			return -1;
		break;
	case CACHE_EXT_UNTRACKED:
		istate->untracked = read_untracked_extension(data, sz);
		break;
	case CACHE_EXT_FSMONITOR:
		read_fsmonitor_extension(istate, data, sz);
		break;
	case CACHE_EXT_ENDOFINDEXENTRIES:
	case CACHE_EXT_INDEXENTRYOFFSETTABLE:
		/* already handled in do_read_index() */
		break;
	default:
		if (*ext < 'A' || 'Z' < *ext)
			return error(_("index uses %.4s extension, which we do not understand"),
				     ext);
		fprintf_ln(stderr, _("ignoring %.4s extension"), ext);
		break;
	}
	return 0;
}