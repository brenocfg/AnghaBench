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
struct sa_handle {int dummy; } ;
struct query_params {int /*<<< orphan*/  cpi; } ;
struct query_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_class_port_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_class_port_info(const struct query_cmd *q, struct sa_handle * h,
				 struct query_params *p, int argc, char *argv[])
{
	dump_class_port_info(&p->cpi);
	return (0);
}