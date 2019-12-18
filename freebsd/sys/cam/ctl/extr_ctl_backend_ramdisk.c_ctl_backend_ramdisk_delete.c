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
typedef  int uint64_t ;
typedef  int u_int ;
struct ctl_be_ramdisk_lun {scalar_t__ pblockmul; } ;
struct ctl_be_lun {int pblockexp; int blocksize; struct ctl_be_ramdisk_lun* be_lun; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  getpage_op_t ;

/* Variables and functions */
 int /*<<< orphan*/  GP_ANCHOR ; 
 int /*<<< orphan*/  GP_OTHER ; 
 int /*<<< orphan*/ * P_ANCHORED ; 
 int /*<<< orphan*/ * P_UNMAPPED ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  ctl_backend_ramdisk_anchorpage (struct ctl_be_ramdisk_lun*,int) ; 
 int /*<<< orphan*/ * ctl_backend_ramdisk_getpage (struct ctl_be_ramdisk_lun*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_backend_ramdisk_unmappage (struct ctl_be_ramdisk_lun*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int min (int,scalar_t__) ; 

__attribute__((used)) static void
ctl_backend_ramdisk_delete(struct ctl_be_lun *cbe_lun, off_t lba, off_t len,
    int anchor)
{
	struct ctl_be_ramdisk_lun *be_lun = cbe_lun->be_lun;
	uint8_t *page;
	uint64_t p, lp;
	u_int lbaoff;
	getpage_op_t op = anchor ? GP_ANCHOR : GP_OTHER;

	/* Partially zero first partial page. */
	p = lba >> cbe_lun->pblockexp;
	lbaoff = lba & ~(UINT_MAX << cbe_lun->pblockexp);
	if (lbaoff != 0) {
		page = ctl_backend_ramdisk_getpage(be_lun, p, op);
		if (page != P_UNMAPPED && page != P_ANCHORED) {
			memset(page + lbaoff * cbe_lun->blocksize, 0,
			    min(len, be_lun->pblockmul - lbaoff) *
			    cbe_lun->blocksize);
		}
		p++;
	}

	/* Partially zero last partial page. */
	lp = (lba + len) >> cbe_lun->pblockexp;
	lbaoff = (lba + len) & ~(UINT_MAX << cbe_lun->pblockexp);
	if (p <= lp && lbaoff != 0) {
		page = ctl_backend_ramdisk_getpage(be_lun, lp, op);
		if (page != P_UNMAPPED && page != P_ANCHORED)
			memset(page, 0, lbaoff * cbe_lun->blocksize);
	}

	/* Delete remaining full pages. */
	if (anchor) {
		for (; p < lp; p++)
			ctl_backend_ramdisk_anchorpage(be_lun, p);
	} else {
		for (; p < lp; p++)
			ctl_backend_ramdisk_unmappage(be_lun, p);
	}
}