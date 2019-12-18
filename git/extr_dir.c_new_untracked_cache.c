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
struct untracked_cache {char* exclude_per_dir; int dir_flags; int /*<<< orphan*/  ident; } ;
struct index_state {int /*<<< orphan*/  cache_changed; struct untracked_cache* untracked; } ;

/* Variables and functions */
 int DIR_HIDE_EMPTY_DIRECTORIES ; 
 int DIR_SHOW_OTHER_DIRECTORIES ; 
 int /*<<< orphan*/  UNTRACKED_CHANGED ; 
 int /*<<< orphan*/  set_untracked_ident (struct untracked_cache*) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int) ; 
 struct untracked_cache* xcalloc (int,int) ; 

__attribute__((used)) static void new_untracked_cache(struct index_state *istate)
{
	struct untracked_cache *uc = xcalloc(1, sizeof(*uc));
	strbuf_init(&uc->ident, 100);
	uc->exclude_per_dir = ".gitignore";
	/* should be the same flags used by git-status */
	uc->dir_flags = DIR_SHOW_OTHER_DIRECTORIES | DIR_HIDE_EMPTY_DIRECTORIES;
	set_untracked_ident(uc);
	istate->untracked = uc;
	istate->cache_changed |= UNTRACKED_CHANGED;
}