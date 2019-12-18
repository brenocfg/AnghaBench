#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vdd {scalar_t__ vdd_type; int max_depth; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct isofile {TYPE_3__* cur_content; TYPE_3__ content; struct isofile* hardlink_target; } ;
struct TYPE_5__ {int cnt; } ;
struct isoent {struct isofile* file; TYPE_2__ children; struct isoent** children_sorted; } ;
struct TYPE_4__ {int /*<<< orphan*/  rr; } ;
struct iso9660 {TYPE_1__ opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_REC_NORMAL ; 
 int /*<<< orphan*/  DIR_REC_PARENT ; 
 int /*<<< orphan*/  DIR_REC_SELF ; 
 int LOGICAL_BLOCK_SIZE ; 
 scalar_t__ VDD_JOLIET ; 
 int get_dir_rec_size (struct iso9660*,struct isoent*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
calculate_directory_descriptors(struct iso9660 *iso9660, struct vdd *vdd,
    struct isoent *isoent, int depth)
{
	struct isoent **enttbl;
	int bs, block, i;

	block = 1;
	bs = get_dir_rec_size(iso9660, isoent, DIR_REC_SELF, vdd->vdd_type);
	bs += get_dir_rec_size(iso9660, isoent, DIR_REC_PARENT, vdd->vdd_type);

	if (isoent->children.cnt <= 0 || (vdd->vdd_type != VDD_JOLIET &&
	    !iso9660->opt.rr && depth + 1 >= vdd->max_depth))
		return (block);

	enttbl = isoent->children_sorted;
	for (i = 0; i < isoent->children.cnt; i++) {
		struct isoent *np = enttbl[i];
		struct isofile *file;

		file = np->file;
		if (file->hardlink_target != NULL)
			file = file->hardlink_target;
		file->cur_content = &(file->content);
		do {
			int dr_l;

			dr_l = get_dir_rec_size(iso9660, np, DIR_REC_NORMAL,
			    vdd->vdd_type);
			if ((bs + dr_l) > LOGICAL_BLOCK_SIZE) {
				block ++;
				bs = dr_l;
			} else
				bs += dr_l;
			file->cur_content = file->cur_content->next;
		} while (file->cur_content != NULL);
	}
	return (block);
}