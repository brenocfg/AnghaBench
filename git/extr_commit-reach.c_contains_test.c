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
typedef  scalar_t__ uint32_t ;
struct contains_cache {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit {scalar_t__ generation; } ;
typedef  enum contains_result { ____Placeholder_contains_result } contains_result ;

/* Variables and functions */
 int CONTAINS_NO ; 
 int CONTAINS_UNKNOWN ; 
 int CONTAINS_YES ; 
 int* contains_cache_at (struct contains_cache*,struct commit*) ; 
 scalar_t__ in_commit_list (struct commit_list const*,struct commit*) ; 
 int /*<<< orphan*/  parse_commit_or_die (struct commit*) ; 

__attribute__((used)) static enum contains_result contains_test(struct commit *candidate,
					  const struct commit_list *want,
					  struct contains_cache *cache,
					  uint32_t cutoff)
{
	enum contains_result *cached = contains_cache_at(cache, candidate);

	/* If we already have the answer cached, return that. */
	if (*cached)
		return *cached;

	/* or are we it? */
	if (in_commit_list(want, candidate)) {
		*cached = CONTAINS_YES;
		return CONTAINS_YES;
	}

	/* Otherwise, we don't know; prepare to recurse */
	parse_commit_or_die(candidate);

	if (candidate->generation < cutoff)
		return CONTAINS_NO;

	return CONTAINS_UNKNOWN;
}