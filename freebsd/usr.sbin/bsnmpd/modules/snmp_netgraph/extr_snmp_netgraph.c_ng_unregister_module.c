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
struct msgreg {struct lmodule const* mod; } ;
struct lmodule {int dummy; } ;
struct datareg {struct lmodule const* mod; } ;

/* Variables and functions */
 struct msgreg* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct msgreg* SLIST_NEXT (struct msgreg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct msgreg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datareg ; 
 int /*<<< orphan*/  datareg_list ; 
 int /*<<< orphan*/  free (struct msgreg*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  msgreg ; 
 int /*<<< orphan*/  msgreg_list ; 

void
ng_unregister_module(const struct lmodule *mod)
{
	struct msgreg *m, *m1;
	struct datareg *d, *d1;

	m = SLIST_FIRST(&msgreg_list);
	while (m != NULL) {
		m1 = SLIST_NEXT(m, link);
		if (m->mod == mod) {
			SLIST_REMOVE(&msgreg_list, m, msgreg, link);
			free(m);
		}
		m = m1;
	}

	d = SLIST_FIRST(&datareg_list);
	while (d != NULL) {
		d1 = SLIST_NEXT(d, link);
		if (d->mod == mod) {
			SLIST_REMOVE(&datareg_list, d, datareg, link);
			free(d);
		}
		d = d1;
	}
}