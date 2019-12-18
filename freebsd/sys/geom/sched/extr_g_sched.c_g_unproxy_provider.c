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
struct g_provider {struct g_geom* geom; } ;
struct g_geom {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_reparent_provider (struct g_provider*,struct g_geom*,struct g_provider*) ; 

__attribute__((used)) static inline void
g_unproxy_provider(struct g_provider *oldpp, struct g_provider *newpp)
{
	struct g_geom *gp = oldpp->geom;

	g_reparent_provider(oldpp, newpp->geom, newpp);

	/*
	 * Hackish: let the system destroy the old provider for us, just
	 * in case someone attached a consumer to it, in which case a
	 * direct call to g_destroy_provider() would not work.
	 */
	g_reparent_provider(newpp, gp, NULL);
}