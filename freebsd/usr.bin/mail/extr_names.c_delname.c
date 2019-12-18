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
struct name {TYPE_1__* n_blink; struct name* n_flink; int /*<<< orphan*/  n_name; } ;
struct TYPE_2__ {struct name* n_flink; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

struct name *
delname(struct name *np, char name[])
{
	struct name *p;

	for (p = np; p != NULL; p = p->n_flink)
		if (strcasecmp(p->n_name, name) == 0) {
			if (p->n_blink == NULL) {
				if (p->n_flink != NULL)
					p->n_flink->n_blink = NULL;
				np = p->n_flink;
				continue;
			}
			if (p->n_flink == NULL) {
				if (p->n_blink != NULL)
					p->n_blink->n_flink = NULL;
				continue;
			}
			p->n_blink->n_flink = p->n_flink;
			p->n_flink->n_blink = p->n_blink;
		}
	return (np);
}