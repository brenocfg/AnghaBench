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
struct g_bde_work {int /*<<< orphan*/ * ksp; int /*<<< orphan*/ * sp; int /*<<< orphan*/  softc; int /*<<< orphan*/  length; int /*<<< orphan*/  bp; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_bde_contribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_bde_delete_sector (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_bde_delete_work (struct g_bde_work*) ; 
 int /*<<< orphan*/  g_bde_release_keysector (struct g_bde_work*) ; 

__attribute__((used)) static void
g_bde_work_done(struct g_bde_work *wp, int error)
{

	g_bde_contribute(wp->bp, wp->length, error);
	if (wp->sp != NULL)
		g_bde_delete_sector(wp->softc, wp->sp);
	if (wp->ksp != NULL)
		g_bde_release_keysector(wp);
	g_bde_delete_work(wp);
}