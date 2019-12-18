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
struct vdd {int max_depth; TYPE_1__* pathtbl; } ;
struct archive_write {int /*<<< orphan*/  archive; } ;
struct TYPE_2__ {scalar_t__ cnt; int /*<<< orphan*/ * sorted; int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static int
isoent_alloc_path_table(struct archive_write *a, struct vdd *vdd,
    int max_depth)
{
	int i;

	vdd->max_depth = max_depth;
	vdd->pathtbl = malloc(sizeof(*vdd->pathtbl) * vdd->max_depth);
	if (vdd->pathtbl == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	for (i = 0; i < vdd->max_depth; i++) {
		vdd->pathtbl[i].first = NULL;
		vdd->pathtbl[i].last = &(vdd->pathtbl[i].first);
		vdd->pathtbl[i].sorted = NULL;
		vdd->pathtbl[i].cnt = 0;
	}
	return (ARCHIVE_OK);
}