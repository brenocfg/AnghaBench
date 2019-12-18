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
struct pmc_event_descr {int /*<<< orphan*/  pm_ev_name; } ;
struct pmc_class_descr {size_t pm_evc_event_table_size; struct pmc_event_descr* pm_evc_event_table; } ;

/* Variables and functions */
 scalar_t__ pmc_match_event_name (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct pmc_event_descr *
pmc_match_event_class(const char *name,
    const struct pmc_class_descr *pcd)
{
	size_t n;
	const struct pmc_event_descr *ev;

	ev = pcd->pm_evc_event_table;
	for (n = 0; n < pcd->pm_evc_event_table_size; n++, ev++)
		if (pmc_match_event_name(name, ev->pm_ev_name))
			return (ev);

	return (NULL);
}