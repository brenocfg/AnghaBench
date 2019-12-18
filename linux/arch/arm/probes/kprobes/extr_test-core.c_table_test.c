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
typedef  union decode_item {int dummy; } decode_item ;
struct table_test_args {union decode_item const* root_table; int /*<<< orphan*/  parent_value; int /*<<< orphan*/  parent_mask; } ;

/* Variables and functions */
 int table_iter (union decode_item const*,int /*<<< orphan*/ ,struct table_test_args*) ; 
 int /*<<< orphan*/  table_test_fn ; 

__attribute__((used)) static int table_test(const union decode_item *table)
{
	struct table_test_args args = {
		.root_table	= table,
		.parent_mask	= 0,
		.parent_value	= 0
	};
	return table_iter(args.root_table, table_test_fn, &args);
}