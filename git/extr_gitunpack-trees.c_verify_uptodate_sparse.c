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
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SPARSE_NOT_UPTODATE_FILE ; 
 int verify_uptodate_1 (struct cache_entry const*,struct unpack_trees_options*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_uptodate_sparse(const struct cache_entry *ce,
				  struct unpack_trees_options *o)
{
	return verify_uptodate_1(ce, o, ERROR_SPARSE_NOT_UPTODATE_FILE);
}