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
struct pathspec {int dummy; } ;
struct index_state {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry const*) ; 
 int match_pathspec (struct index_state const*,struct pathspec const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline int ce_path_match(const struct index_state *istate,
				const struct cache_entry *ce,
				const struct pathspec *pathspec,
				char *seen)
{
	return match_pathspec(istate, pathspec, ce->name, ce_namelen(ce), 0, seen,
			      S_ISDIR(ce->ce_mode) || S_ISGITLINK(ce->ce_mode));
}