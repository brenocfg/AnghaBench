#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct table_config {scalar_t__ linked; int /*<<< orphan*/  ti_copy; int /*<<< orphan*/  astate; TYPE_1__* ta; } ;
struct namedobj_instance {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  free (struct table_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_table_config(struct namedobj_instance *ni, struct table_config *tc)
{

	KASSERT(tc->linked == 0, ("free() on linked config"));
	/* UH lock MUST NOT be held */

	/*
	 * We're using ta without any locking/referencing.
	 * TODO: fix this if we're going to use unloadable algos.
	 */
	tc->ta->destroy(tc->astate, &tc->ti_copy);
	free(tc, M_IPFW);
}