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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
struct ecore_bmap {unsigned long* bitmap; int max_count; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int,...) ; 
 int OSAL_BITMAP_WEIGHT (unsigned long*,int) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned long* OSAL_NULL ; 
 int OSAL_SPRINTF (int /*<<< orphan*/ *,char*,unsigned long long) ; 

void ecore_rdma_bmap_free(struct ecore_hwfn *p_hwfn,
			  struct ecore_bmap *bmap,
			  bool check)
{
	int weight, line, item, last_line, last_item;
	u64 *pmap;

	if (!bmap || !bmap->bitmap)
		return;

	if (!check)
		goto end;

	weight = OSAL_BITMAP_WEIGHT(bmap->bitmap, bmap->max_count);
	if (!weight)
		goto end;

	DP_NOTICE(p_hwfn, false,
		  "%s bitmap not free - size=%d, weight=%d, 512 bits per line\n",
		  bmap->name, bmap->max_count, weight);

	pmap = (u64 *)bmap->bitmap;
	last_line = bmap->max_count / (64*8);
	last_item = last_line * 8 + (((bmap->max_count % (64*8)) + 63) / 64);

	/* print aligned non-zero lines, if any */
	for (item = 0, line = 0; line < last_line; line++, item += 8) {
		if (OSAL_BITMAP_WEIGHT((unsigned long *)&pmap[item], 64*8))
			DP_NOTICE(p_hwfn, false,
				  "line 0x%04x: 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx\n",
				  line, (unsigned long long)pmap[item],
				(unsigned long long)pmap[item+1],
				(unsigned long long)pmap[item+2],
				  (unsigned long long)pmap[item+3],
				(unsigned long long)pmap[item+4],
				(unsigned long long)pmap[item+5],
				  (unsigned long long)pmap[item+6],
				(unsigned long long)pmap[item+7]);
	}

	/* print last unaligned non-zero line, if any */
	if ((bmap->max_count % (64*8)) &&
	    (OSAL_BITMAP_WEIGHT((unsigned long *)&pmap[item],
				bmap->max_count-item*64))) {
		u8 str_last_line[200] = { 0 };
		int  offset;

		offset = OSAL_SPRINTF(str_last_line, "line 0x%04x: ", line);
		for (; item < last_item; item++) {
			offset += OSAL_SPRINTF(str_last_line+offset,
					       "0x%016llx ",
				(unsigned long long)pmap[item]);
		}
		DP_NOTICE(p_hwfn, false, "%s\n", str_last_line);
	}

end:
	OSAL_FREE(p_hwfn->p_dev, bmap->bitmap);
	bmap->bitmap = OSAL_NULL;
}