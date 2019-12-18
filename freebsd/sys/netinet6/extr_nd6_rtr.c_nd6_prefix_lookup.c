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
struct nd_prefixctl {int dummy; } ;
struct nd_prefix {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND6_RLOCK () ; 
 int /*<<< orphan*/  ND6_RUNLOCK () ; 
 struct nd_prefix* nd6_prefix_lookup_locked (struct nd_prefixctl*) ; 

struct nd_prefix *
nd6_prefix_lookup(struct nd_prefixctl *key)
{
	struct nd_prefix *search;

	ND6_RLOCK();
	search = nd6_prefix_lookup_locked(key);
	ND6_RUNLOCK();
	return (search);
}