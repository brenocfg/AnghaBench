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
typedef  int /*<<< orphan*/  uint8_t ;
struct ctl_be_ramdisk_lun {scalar_t__ cap_bytes; int indir; scalar_t__ cap_used; scalar_t__ pblocksize; int /*<<< orphan*/  page_lock; int /*<<< orphan*/ ** pages; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_RAMDISK ; 
 int PPPS ; 
 int /*<<< orphan*/ ** P_ANCHORED ; 
 int /*<<< orphan*/ ** P_UNMAPPED ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ctl_backend_ramdisk_anchorpage(struct ctl_be_ramdisk_lun *be_lun, off_t pn)
{
	uint8_t ***pp;
	off_t i;
	int s;

	if (be_lun->cap_bytes == 0)
		return;
	sx_xlock(&be_lun->page_lock);
	pp = &be_lun->pages;
	for (s = (be_lun->indir - 1) * PPPS; s >= 0; s -= PPPS) {
		if (*pp == NULL)
			goto noindir;
		i = pn >> s;
		pp = (uint8_t ***)&(*pp)[i];
		pn -= i << s;
	}
	if (*pp == P_UNMAPPED && be_lun->cap_used < be_lun->cap_bytes) {
		be_lun->cap_used += be_lun->pblocksize;
		*pp = P_ANCHORED;
	} else if (*pp != P_ANCHORED) {
		free(*pp, M_RAMDISK);
		*pp = P_ANCHORED;
	}
noindir:
	sx_xunlock(&be_lun->page_lock);
}