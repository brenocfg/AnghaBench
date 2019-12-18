#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct g_provider* zv_provider; } ;
typedef  TYPE_1__ zvol_state_t ;
struct g_provider {scalar_t__ name; } ;
typedef  int /*<<< orphan*/  ZVOL_DRIVER ;

/* Variables and functions */
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_kthread_add (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  system_proc ; 
 int /*<<< orphan*/  zvol_geom_worker ; 

__attribute__((used)) static void
zvol_geom_run(zvol_state_t *zv)
{
	struct g_provider *pp;

	pp = zv->zv_provider;
	g_error_provider(pp, 0);

	kproc_kthread_add(zvol_geom_worker, zv, &system_proc, NULL, 0, 0,
	    "zfskern", "zvol %s", pp->name + sizeof(ZVOL_DRIVER));
}