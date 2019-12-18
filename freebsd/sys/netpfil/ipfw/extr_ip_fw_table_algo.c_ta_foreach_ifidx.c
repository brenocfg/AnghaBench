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
typedef  int /*<<< orphan*/  ta_foreach_f ;
struct wa_ifidx {void* arg; int /*<<< orphan*/ * f; } ;
struct table_info {int dummy; } ;
struct iftable_cfg {int /*<<< orphan*/  ii; } ;

/* Variables and functions */
 int /*<<< orphan*/  foreach_ifidx ; 
 int /*<<< orphan*/  ipfw_objhash_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wa_ifidx*) ; 

__attribute__((used)) static void
ta_foreach_ifidx(void *ta_state, struct table_info *ti, ta_foreach_f *f,
    void *arg)
{
	struct iftable_cfg *icfg;
	struct wa_ifidx wa;

	icfg = (struct iftable_cfg *)ta_state;

	wa.f = f;
	wa.arg = arg;

	ipfw_objhash_foreach(icfg->ii, foreach_ifidx, &wa);
}