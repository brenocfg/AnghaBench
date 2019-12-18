#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct ddf_vdc_record {int /*<<< orphan*/  Block_Count; int /*<<< orphan*/ * Physical_Disk_Sequence; int /*<<< orphan*/  Primary_Element_Count; int /*<<< orphan*/  Signature; } ;
struct ddf_meta {int dummy; } ;
typedef  scalar_t__ off_t ;
struct TYPE_8__ {int /*<<< orphan*/  Max_Primary_Element_Entries; } ;
struct TYPE_7__ {int /*<<< orphan*/  PD_Reference; } ;
struct TYPE_6__ {TYPE_1__* entry; } ;
struct TYPE_5__ {int /*<<< orphan*/  Configured_Size; } ;

/* Variables and functions */
 scalar_t__ DDF_VDCR_SIGNATURE ; 
 size_t GET16 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GET16D (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET32 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET32D (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET64 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET64D (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET64P (struct ddf_meta*,int /*<<< orphan*/ *) ; 
 int GETCRNUM (struct ddf_meta*) ; 
 struct ddf_vdc_record* GETVDCPTR (struct ddf_meta*,int) ; 
 int ddf_meta_find_pd (struct ddf_meta*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_4__* hdr ; 
 TYPE_3__* pdd ; 
 TYPE_2__* pdr ; 

__attribute__((used)) static int
ddf_meta_unused_range(struct ddf_meta *meta, off_t *off, off_t *size)
{
	struct ddf_vdc_record *vdc;
	off_t beg[32], end[32], beg1, end1;
	uint64_t *offp;
	int i, j, n, num, pos;
	uint32_t ref;

	*off = 0;
	*size = 0;
	ref = GET32(meta, pdd->PD_Reference);
	pos = ddf_meta_find_pd(meta, NULL, ref);
	beg[0] = 0;
	end[0] = GET64(meta, pdr->entry[pos].Configured_Size);
	n = 1;
	num = GETCRNUM(meta);
	for (i = 0; i < num; i++) {
		vdc = GETVDCPTR(meta, i);
		if (GET32D(meta, vdc->Signature) != DDF_VDCR_SIGNATURE)
			continue;
		for (pos = 0; pos < GET16D(meta, vdc->Primary_Element_Count); pos++)
			if (GET32D(meta, vdc->Physical_Disk_Sequence[pos]) == ref)
				break;
		if (pos == GET16D(meta, vdc->Primary_Element_Count))
			continue;
		offp = (uint64_t *)&(vdc->Physical_Disk_Sequence[
		    GET16(meta, hdr->Max_Primary_Element_Entries)]);
		beg1 = GET64P(meta, offp + pos);
		end1 = beg1 + GET64D(meta, vdc->Block_Count);
		for (j = 0; j < n; j++) {
			if (beg[j] >= end1 || end[j] <= beg1 )
				continue;
			if (beg[j] < beg1 && end[j] > end1) {
				beg[n] = end1;
				end[n] = end[j];
				end[j] = beg1;
				n++;
			} else if (beg[j] < beg1)
				end[j] = beg1;
			else
				beg[j] = end1;
		}
	}
	for (j = 0; j < n; j++) {
		if (end[j] - beg[j] > *size) {
			*off = beg[j];
			*size = end[j] - beg[j];
		}
	}
	return ((*size > 0) ? 1 : 0);
}