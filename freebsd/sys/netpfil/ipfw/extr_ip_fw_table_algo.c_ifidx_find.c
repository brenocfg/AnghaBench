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
struct table_info {int /*<<< orphan*/  data; int /*<<< orphan*/  state; } ;
struct ifidx {int dummy; } ;

/* Variables and functions */
 struct ifidx* bsearch (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_ifidx ; 

__attribute__((used)) static struct ifidx *
ifidx_find(struct table_info *ti, void *key)
{
	struct ifidx *ifi;

	ifi = bsearch(key, ti->state, ti->data, sizeof(struct ifidx),
	    compare_ifidx);

	return (ifi);
}