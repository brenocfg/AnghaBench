#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct TYPE_3__ {int /*<<< orphan*/  sa; } ;
struct secpolicyindex {scalar_t__ prefs; scalar_t__ prefd; scalar_t__ ul_proto; scalar_t__ dir; TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 scalar_t__ key_sockaddrcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
key_cmpspidx_exactly(struct secpolicyindex *spidx0,
    struct secpolicyindex *spidx1)
{
	/* sanity */
	if (spidx0 == NULL && spidx1 == NULL)
		return 1;

	if (spidx0 == NULL || spidx1 == NULL)
		return 0;

	if (spidx0->prefs != spidx1->prefs
	 || spidx0->prefd != spidx1->prefd
	 || spidx0->ul_proto != spidx1->ul_proto
	 || spidx0->dir != spidx1->dir)
		return 0;

	return key_sockaddrcmp(&spidx0->src.sa, &spidx1->src.sa, 1) == 0 &&
	       key_sockaddrcmp(&spidx0->dst.sa, &spidx1->dst.sa, 1) == 0;
}