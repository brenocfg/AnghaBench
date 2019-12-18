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
struct nl_parser_param {scalar_t__ pp_arg; } ;
struct nl_object {int dummy; } ;
struct nl_cache {int dummy; } ;

/* Variables and functions */
 int nl_cache_add (struct nl_cache*,struct nl_object*) ; 

__attribute__((used)) static int pickup_cb(struct nl_object *c, struct nl_parser_param *p)
{
	return nl_cache_add((struct nl_cache *) p->pp_arg, c);
}