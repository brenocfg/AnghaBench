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
struct vdd {int max_depth; int /*<<< orphan*/ * pathtbl; struct isoent* rootent; } ;
struct TYPE_2__ {struct isoent* first; } ;
struct isoent {struct isoent* drnext; struct isoent* parent; TYPE_1__ subdirs; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  path_table_add_entry (int /*<<< orphan*/ *,struct isoent*) ; 

__attribute__((used)) static int
isoent_collect_dirs(struct vdd *vdd, struct isoent *rootent, int depth)
{
	struct isoent *np;

	if (rootent == NULL)
		rootent = vdd->rootent;
	np = rootent;
	do {
		/* Register current directory to pathtable. */
		path_table_add_entry(&(vdd->pathtbl[depth]), np);

		if (np->subdirs.first != NULL && depth + 1 < vdd->max_depth) {
			/* Enter to sub directories. */
			np = np->subdirs.first;
			depth++;
			continue;
		}
		while (np != rootent) {
			if (np->drnext == NULL) {
				/* Return to the parent directory. */
				np = np->parent;
				depth--;
			} else {
				np = np->drnext;
				break;
			}
		}
	} while (np != rootent);

	return (ARCHIVE_OK);
}