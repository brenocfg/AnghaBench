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
struct line_log_data {scalar_t__ pair; int /*<<< orphan*/  ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  diff_free_filepair (scalar_t__) ; 
 int /*<<< orphan*/  range_set_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void line_log_data_clear(struct line_log_data *r)
{
	range_set_release(&r->ranges);
	if (r->pair)
		diff_free_filepair(r->pair);
}