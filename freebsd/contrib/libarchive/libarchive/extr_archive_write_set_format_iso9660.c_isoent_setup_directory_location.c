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
struct vdd {int max_depth; scalar_t__ total_dir_block; struct isoent* rootent; } ;
struct TYPE_2__ {struct isoent* first; } ;
struct isoent {int dir_location; struct isoent* drnext; struct isoent* parent; TYPE_1__ subdirs; scalar_t__ dir_block; } ;
struct iso9660 {int dummy; } ;

/* Variables and functions */
 scalar_t__ calculate_directory_descriptors (struct iso9660*,struct vdd*,struct isoent*,int) ; 
 int extra_setup_location (struct isoent*,int) ; 

__attribute__((used)) static void
isoent_setup_directory_location(struct iso9660 *iso9660, int location,
    struct vdd *vdd)
{
	struct isoent *np;
	int depth;

	vdd->total_dir_block = 0;
	depth = 0;
	np = vdd->rootent;
	do {
		int block;

		np->dir_block = calculate_directory_descriptors(
		    iso9660, vdd, np, depth);
		vdd->total_dir_block += np->dir_block;
		np->dir_location = location;
		location += np->dir_block;
		block = extra_setup_location(np, location);
		vdd->total_dir_block += block;
		location += block;

		if (np->subdirs.first != NULL && depth + 1 < vdd->max_depth) {
			/* Enter to sub directories. */
			np = np->subdirs.first;
			depth++;
			continue;
		}
		while (np != np->parent) {
			if (np->drnext == NULL) {
				/* Return to the parent directory. */
				np = np->parent;
				depth--;
			} else {
				np = np->drnext;
				break;
			}
		}
	} while (np != np->parent);
}