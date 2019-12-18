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
struct g_provider {scalar_t__ acw; scalar_t__ error; TYPE_1__* geom; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EV_CANCEL ; 
 int G_GEOM_WITHER ; 
 int /*<<< orphan*/  G_VALID_PROVIDER (struct g_provider*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  g_new_provider_event ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct g_provider*,int /*<<< orphan*/ ,struct g_provider*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_spoil_event (void*,int) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_media_changed_event(void *arg, int flag)
{
	struct g_provider *pp;
	int retaste;

	g_topology_assert();
	if (flag == EV_CANCEL)
		return;
	pp = arg;
	G_VALID_PROVIDER(pp);

	/*
	 * If provider was not open for writing, queue retaste after spoiling.
	 * If it was, retaste will happen automatically on close.
	 */
	retaste = (pp->acw == 0 && pp->error == 0 &&
	    !(pp->geom->flags & G_GEOM_WITHER));
	g_spoil_event(arg, flag);
	if (retaste)
		g_post_event(g_new_provider_event, pp, M_WAITOK, pp, NULL);
}