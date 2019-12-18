#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vdd {scalar_t__ vdd_type; int max_depth; struct isoent* rootent; } ;
struct TYPE_4__ {struct isoent* first; } ;
struct TYPE_3__ {struct extr_rec* first; } ;
struct isoent {struct isoent* drnext; struct isoent* parent; TYPE_2__ subdirs; TYPE_1__ extr_rec_list; } ;
struct extr_rec {int offset; int /*<<< orphan*/  buf; struct extr_rec* next; } ;
struct archive_write {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int LOGICAL_BLOCK_SIZE ; 
 scalar_t__ VDD_JOLIET ; 
 int _write_directory_descriptors (struct archive_write*,struct vdd*,struct isoent*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 unsigned char* wb_buffptr (struct archive_write*) ; 
 int wb_consume (struct archive_write*,int) ; 

__attribute__((used)) static int
write_directory_descriptors(struct archive_write *a, struct vdd *vdd)
{
	struct isoent *np;
	int depth, r;

	depth = 0;
	np = vdd->rootent;
	do {
		struct extr_rec *extr;

		r = _write_directory_descriptors(a, vdd, np, depth);
		if (r < 0)
			return (r);
		if (vdd->vdd_type != VDD_JOLIET) {
			/*
			 * This extract record is used by SUSP,RRIP.
			 * Not for joliet.
			 */
			for (extr = np->extr_rec_list.first;
			    extr != NULL;
			    extr = extr->next) {
				unsigned char *wb;

				wb = wb_buffptr(a);
				memcpy(wb, extr->buf, extr->offset);
				memset(wb + extr->offset, 0,
				    LOGICAL_BLOCK_SIZE - extr->offset);
				r = wb_consume(a, LOGICAL_BLOCK_SIZE);
				if (r < 0)
					return (r);
			}
		}

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

	return (ARCHIVE_OK);
}