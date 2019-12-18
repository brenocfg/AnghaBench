#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * bitmaps; int /*<<< orphan*/ * spares; int /*<<< orphan*/  h_charkey; int /*<<< orphan*/  hdrpages; int /*<<< orphan*/  nkeys; int /*<<< orphan*/  ffactor; int /*<<< orphan*/  low_mask; int /*<<< orphan*/  high_mask; int /*<<< orphan*/  max_bucket; int /*<<< orphan*/  last_freed; int /*<<< orphan*/  ovfl_point; int /*<<< orphan*/  sshift; int /*<<< orphan*/  ssize; int /*<<< orphan*/  dsize; int /*<<< orphan*/  bshift; int /*<<< orphan*/  bsize; int /*<<< orphan*/  lorder; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
struct TYPE_4__ {TYPE_2__ hdr; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ HASHHDR ;

/* Variables and functions */
 int /*<<< orphan*/  M_16_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_32_SWAP (int /*<<< orphan*/ ) ; 
 int NCACHED ; 

__attribute__((used)) static void
swap_header(HTAB *hashp)
{
	HASHHDR *hdrp;
	int i;

	hdrp = &hashp->hdr;

	M_32_SWAP(hdrp->magic);
	M_32_SWAP(hdrp->version);
	M_32_SWAP(hdrp->lorder);
	M_32_SWAP(hdrp->bsize);
	M_32_SWAP(hdrp->bshift);
	M_32_SWAP(hdrp->dsize);
	M_32_SWAP(hdrp->ssize);
	M_32_SWAP(hdrp->sshift);
	M_32_SWAP(hdrp->ovfl_point);
	M_32_SWAP(hdrp->last_freed);
	M_32_SWAP(hdrp->max_bucket);
	M_32_SWAP(hdrp->high_mask);
	M_32_SWAP(hdrp->low_mask);
	M_32_SWAP(hdrp->ffactor);
	M_32_SWAP(hdrp->nkeys);
	M_32_SWAP(hdrp->hdrpages);
	M_32_SWAP(hdrp->h_charkey);
	for (i = 0; i < NCACHED; i++) {
		M_32_SWAP(hdrp->spares[i]);
		M_16_SWAP(hdrp->bitmaps[i]);
	}
}