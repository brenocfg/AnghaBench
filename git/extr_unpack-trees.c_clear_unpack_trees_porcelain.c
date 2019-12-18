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
struct unpack_trees_options {int /*<<< orphan*/  msgs; int /*<<< orphan*/  msgs_to_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void clear_unpack_trees_porcelain(struct unpack_trees_options *opts)
{
	argv_array_clear(&opts->msgs_to_free);
	memset(opts->msgs, 0, sizeof(opts->msgs));
}