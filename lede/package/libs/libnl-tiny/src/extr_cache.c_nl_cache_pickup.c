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
struct nl_sock {int dummy; } ;
struct nl_parser_param {struct nl_cache* pp_arg; int /*<<< orphan*/  pp_cb; } ;
struct nl_cache {int dummy; } ;

/* Variables and functions */
 int __cache_pickup (struct nl_sock*,struct nl_cache*,struct nl_parser_param*) ; 
 int /*<<< orphan*/  pickup_cb ; 

int nl_cache_pickup(struct nl_sock *sk, struct nl_cache *cache)
{
	struct nl_parser_param p = {
		.pp_cb = pickup_cb,
		.pp_arg = cache,
	};

	return __cache_pickup(sk, cache, &p);
}