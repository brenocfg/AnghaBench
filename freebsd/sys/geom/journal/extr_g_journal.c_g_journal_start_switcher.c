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
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GJ_SWITCHER_WORKING ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_journal_switcher ; 
 int /*<<< orphan*/ * g_journal_switcher_proc ; 
 int /*<<< orphan*/  g_journal_switcher_state ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int kproc_create (int /*<<< orphan*/ ,struct g_class*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
g_journal_start_switcher(struct g_class *mp)
{
	int error;

	g_topology_assert();
	MPASS(g_journal_switcher_proc == NULL);
	g_journal_switcher_state = GJ_SWITCHER_WORKING;
	error = kproc_create(g_journal_switcher, mp, &g_journal_switcher_proc,
	    0, 0, "g_journal switcher");
	KASSERT(error == 0, ("Cannot create switcher thread."));
}