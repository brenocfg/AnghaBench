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
struct archive_write {struct iso9660* format_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_REC_NORMAL ; 
 int /*<<< orphan*/  DIR_REC_PARENT ; 
 int /*<<< orphan*/  DIR_REC_SELF ; 
 int /*<<< orphan*/  LOGICAL_BLOCK_SIZE ; 
 scalar_t__ VDD_JOLIET ; 
 int /*<<< orphan*/  WD_REMAINING ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_directory_record (unsigned char*,int /*<<< orphan*/ ,struct isoent*,struct iso9660*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char* wb_buffptr (struct archive_write*) ; 
 int wb_consume (struct archive_write*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_write_directory_descriptors(struct archive_write *a, struct vdd *vdd,
    struct isoent *isoent, int depth)
{
	struct iso9660 *iso9660 = a->format_data;
	struct isoent **enttbl;
	unsigned char *p, *wb;
	int i, r;
	int dr_l;

	p = wb = wb_buffptr(a);
#define WD_REMAINING	(LOGICAL_BLOCK_SIZE - (p - wb))
	p += set_directory_record(p, WD_REMAINING, isoent,
	    iso9660, DIR_REC_SELF, vdd->vdd_type);
	p += set_directory_record(p, WD_REMAINING, isoent,
	    iso9660, DIR_REC_PARENT, vdd->vdd_type);

	if (isoent->children.cnt <= 0 || (vdd->vdd_type != VDD_JOLIET &&
	    !iso9660->opt.rr && depth + 1 >= vdd->max_depth)) {
		memset(p, 0, WD_REMAINING);
		return (wb_consume(a, LOGICAL_BLOCK_SIZE));
	}

	enttbl = isoent->children_sorted;
	for (i = 0; i < isoent->children.cnt; i++) {
		struct isoent *np = enttbl[i];
		struct isofile *file = np->file;

		if (file->hardlink_target != NULL)
			file = file->hardlink_target;
		file->cur_content = &(file->content);
		do {
			dr_l = set_directory_record(p, WD_REMAINING,
			    np, iso9660, DIR_REC_NORMAL,
			    vdd->vdd_type);
			if (dr_l == 0) {
				memset(p, 0, WD_REMAINING);
				r = wb_consume(a, LOGICAL_BLOCK_SIZE);
				if (r < 0)
					return (r);
				p = wb = wb_buffptr(a);
				dr_l = set_directory_record(p,
				    WD_REMAINING, np, iso9660,
				    DIR_REC_NORMAL, vdd->vdd_type);
			}
			p += dr_l;
			file->cur_content = file->cur_content->next;
		} while (file->cur_content != NULL);
	}
	memset(p, 0, WD_REMAINING);
	return (wb_consume(a, LOGICAL_BLOCK_SIZE));
}