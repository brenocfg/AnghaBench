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
struct nl_parser_param {struct dp_xdata* pp_arg; } ;
struct nl_object {int dummy; } ;
struct dp_xdata {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (struct nl_object*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nl_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_cb(struct nl_object *obj, struct nl_parser_param *p)
{
	struct dp_xdata *x = p->pp_arg;

	x->cb(obj, x->arg);
	return 0;
}