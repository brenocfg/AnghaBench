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
struct g_gsched {int dummy; } ;
struct g_geom {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_sched_lock (struct g_geom*) ; 
 int g_sched_remove_locked (struct g_geom*,struct g_gsched*) ; 
 int /*<<< orphan*/  g_sched_unlock (struct g_geom*) ; 

__attribute__((used)) static int
g_sched_remove(struct g_geom *gp, struct g_gsched *gsp)
{
	int error;

	g_sched_lock(gp);
	error = g_sched_remove_locked(gp, gsp); /* gsp is surely non-null */
	g_sched_unlock(gp);

	return (error);
}