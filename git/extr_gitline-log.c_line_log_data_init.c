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
struct line_log_data {int /*<<< orphan*/  ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct line_log_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  range_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void line_log_data_init(struct line_log_data *r)
{
	memset(r, 0, sizeof(struct line_log_data));
	range_set_init(&r->ranges, 0);
}