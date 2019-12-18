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
struct update_xdata {int /*<<< orphan*/  params; int /*<<< orphan*/  ops; } ;
struct nl_msg {int /*<<< orphan*/  nm_nlh; int /*<<< orphan*/  nm_src; } ;

/* Variables and functions */
 int nl_cache_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_msg_parser(struct nl_msg *msg, void *arg)
{
	struct update_xdata *x = arg;
	
	return nl_cache_parse(x->ops, &msg->nm_src, msg->nm_nlh, x->params);
}