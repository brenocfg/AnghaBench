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
struct prison {int /*<<< orphan*/  pr_mtx; struct prison* pr_parent; } ;
struct linux_prison {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  linux_osd_jail_slot ; 
 struct linux_prison lprison0 ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct linux_prison* osd_jail_get (struct prison*,int /*<<< orphan*/ ) ; 
 struct prison prison0 ; 

__attribute__((used)) static struct linux_prison *
linux_find_prison(struct prison *spr, struct prison **prp)
{
	struct prison *pr;
	struct linux_prison *lpr;

	for (pr = spr;; pr = pr->pr_parent) {
		mtx_lock(&pr->pr_mtx);
		lpr = (pr == &prison0)
		    ? &lprison0
		    : osd_jail_get(pr, linux_osd_jail_slot);
		if (lpr != NULL)
			break;
		mtx_unlock(&pr->pr_mtx);
	}
	*prp = pr;

	return (lpr);
}