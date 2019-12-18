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
struct unpack_trees_options {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int check_submodule_move_head (struct cache_entry const*,char const*,int /*<<< orphan*/ ,struct unpack_trees_options*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submodule_from_ce (struct cache_entry const*) ; 

__attribute__((used)) static int verify_clean_submodule(const char *old_sha1,
				  const struct cache_entry *ce,
				  struct unpack_trees_options *o)
{
	if (!submodule_from_ce(ce))
		return 0;

	return check_submodule_move_head(ce, old_sha1,
					 oid_to_hex(&ce->oid), o);
}