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
struct TYPE_2__ {struct isoent* first; } ;
struct isoent {struct isoent* chnext; struct isoent* parent; TYPE_1__ children; scalar_t__ dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  _isoent_free (struct isoent*) ; 

__attribute__((used)) static void
isoent_free_all(struct isoent *isoent)
{
	struct isoent *np, *np_temp;

	if (isoent == NULL)
		return;
	np = isoent;
	for (;;) {
		if (np->dir) {
			if (np->children.first != NULL) {
				/* Enter to sub directories. */
				np = np->children.first;
				continue;
			}
		}
		for (;;) {
			np_temp = np;
			if (np->chnext == NULL) {
				/* Return to the parent directory. */
				np = np->parent;
				_isoent_free(np_temp);
				if (np == np_temp)
					return;
			} else {
				np = np->chnext;
				_isoent_free(np_temp);
				break;
			}
		}
	}
}