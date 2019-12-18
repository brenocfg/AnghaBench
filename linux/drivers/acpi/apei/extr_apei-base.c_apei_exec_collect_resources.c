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
struct apei_resources {int dummy; } ;
struct apei_exec_context {int dummy; } ;

/* Variables and functions */
 int apei_exec_for_each_entry (struct apei_exec_context*,int /*<<< orphan*/ ,struct apei_resources*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  collect_res_callback ; 

int apei_exec_collect_resources(struct apei_exec_context *ctx,
				struct apei_resources *resources)
{
	return apei_exec_for_each_entry(ctx, collect_res_callback,
					resources, NULL);
}