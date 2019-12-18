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
struct nl_parser_param {struct nl_cache* pp_arg; int /*<<< orphan*/  pp_cb; } ;
struct nl_msg {int dummy; } ;
struct nl_cache {int /*<<< orphan*/  c_ops; } ;

/* Variables and functions */
 int nl_cache_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nl_parser_param*) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct nl_msg*) ; 
 int /*<<< orphan*/  pickup_cb ; 

int nl_cache_parse_and_add(struct nl_cache *cache, struct nl_msg *msg)
{
	struct nl_parser_param p = {
		.pp_cb = pickup_cb,
		.pp_arg = cache,
	};

	return nl_cache_parse(cache->c_ops, NULL, nlmsg_hdr(msg), &p);
}