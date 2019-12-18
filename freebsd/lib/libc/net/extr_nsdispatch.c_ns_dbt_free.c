#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ name; int /*<<< orphan*/  srclistsize; int /*<<< orphan*/  srclist; } ;
typedef  TYPE_1__ ns_dbt ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  ns_src_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ns_dbt_free(ns_dbt *dbt)
{
	ns_src_free(&dbt->srclist, dbt->srclistsize);
	if (dbt->name)
		free((void *)dbt->name);
}