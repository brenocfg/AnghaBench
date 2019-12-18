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
typedef  struct vm_page* vm_page_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct vm_page {int dummy; } ;
struct nvdimm_spa_dev {scalar_t__ spa_phys_base; int /*<<< orphan*/  spa_memattr; } ;
struct bio {int bio_ma_n; int bio_offset; int bio_ma_offset; int /*<<< orphan*/  bio_length; struct vm_page** bio_ma; } ;
typedef  int /*<<< orphan*/  maa ;

/* Variables and functions */
 int BIO_READ ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bzero (struct vm_page*,int) ; 
 int nitems (struct vm_page**) ; 
 int /*<<< orphan*/  pmap_copy_pages (struct vm_page**,int,struct vm_page**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ trunc_page (int) ; 
 int /*<<< orphan*/  vm_page_initfake (struct vm_page*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvdimm_spa_g_all_unmapped(struct nvdimm_spa_dev *dev, struct bio *bp, int rw)
{
	struct vm_page maa[bp->bio_ma_n];
	vm_page_t ma[bp->bio_ma_n];
	vm_memattr_t mattr;
	int i;

	mattr = dev->spa_memattr;
	for (i = 0; i < nitems(ma); i++) {
		bzero(&maa[i], sizeof(maa[i]));
		vm_page_initfake(&maa[i], dev->spa_phys_base +
		    trunc_page(bp->bio_offset) + PAGE_SIZE * i, mattr);
		ma[i] = &maa[i];
	}
	if (rw == BIO_READ)
		pmap_copy_pages(ma, bp->bio_offset & PAGE_MASK, bp->bio_ma,
		    bp->bio_ma_offset, bp->bio_length);
	else
		pmap_copy_pages(bp->bio_ma, bp->bio_ma_offset, ma,
		    bp->bio_offset & PAGE_MASK, bp->bio_length);
}