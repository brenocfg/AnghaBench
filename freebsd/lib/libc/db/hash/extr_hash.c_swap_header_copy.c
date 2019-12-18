#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * bitmaps; int /*<<< orphan*/ * spares; int /*<<< orphan*/  h_charkey; int /*<<< orphan*/  hdrpages; int /*<<< orphan*/  nkeys; int /*<<< orphan*/  ffactor; int /*<<< orphan*/  low_mask; int /*<<< orphan*/  high_mask; int /*<<< orphan*/  max_bucket; int /*<<< orphan*/  last_freed; int /*<<< orphan*/  ovfl_point; int /*<<< orphan*/  sshift; int /*<<< orphan*/  ssize; int /*<<< orphan*/  dsize; int /*<<< orphan*/  bshift; int /*<<< orphan*/  bsize; int /*<<< orphan*/  lorder; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ HASHHDR ;

/* Variables and functions */
 int NCACHED ; 
 int /*<<< orphan*/  P_16_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_32_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
swap_header_copy(HASHHDR *srcp, HASHHDR *destp)
{
	int i;

	P_32_COPY(srcp->magic, destp->magic);
	P_32_COPY(srcp->version, destp->version);
	P_32_COPY(srcp->lorder, destp->lorder);
	P_32_COPY(srcp->bsize, destp->bsize);
	P_32_COPY(srcp->bshift, destp->bshift);
	P_32_COPY(srcp->dsize, destp->dsize);
	P_32_COPY(srcp->ssize, destp->ssize);
	P_32_COPY(srcp->sshift, destp->sshift);
	P_32_COPY(srcp->ovfl_point, destp->ovfl_point);
	P_32_COPY(srcp->last_freed, destp->last_freed);
	P_32_COPY(srcp->max_bucket, destp->max_bucket);
	P_32_COPY(srcp->high_mask, destp->high_mask);
	P_32_COPY(srcp->low_mask, destp->low_mask);
	P_32_COPY(srcp->ffactor, destp->ffactor);
	P_32_COPY(srcp->nkeys, destp->nkeys);
	P_32_COPY(srcp->hdrpages, destp->hdrpages);
	P_32_COPY(srcp->h_charkey, destp->h_charkey);
	for (i = 0; i < NCACHED; i++) {
		P_32_COPY(srcp->spares[i], destp->spares[i]);
		P_16_COPY(srcp->bitmaps[i], destp->bitmaps[i]);
	}
}