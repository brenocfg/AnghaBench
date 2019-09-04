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
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_WOULD_OVERWRITE ; 
 int add_rejected_path (struct unpack_trees_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reject_merge(const struct cache_entry *ce,
			struct unpack_trees_options *o)
{
	return add_rejected_path(o, ERROR_WOULD_OVERWRITE, ce->name);
}