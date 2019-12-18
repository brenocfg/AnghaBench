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
struct ddf_vdc_record {int /*<<< orphan*/  VD_GUID; int /*<<< orphan*/  Signature; } ;
struct ddf_meta {int dummy; } ;

/* Variables and functions */
 scalar_t__ DDF_VDCR_SIGNATURE ; 
 scalar_t__ GET32D (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GETCRNUM (struct ddf_meta*) ; 
 struct ddf_vdc_record* GETVDCPTR (struct ddf_meta*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ddf_meta_count_vdc(struct ddf_meta *meta, uint8_t *GUID)
{
	struct ddf_vdc_record *vdc;
	int i, num, cnt;

	cnt = 0;
	num = GETCRNUM(meta);
	for (i = 0; i < num; i++) {
		vdc = GETVDCPTR(meta, i);
		if (GET32D(meta, vdc->Signature) != DDF_VDCR_SIGNATURE)
			continue;
		if (GUID == NULL || memcmp(vdc->VD_GUID, GUID, 24) == 0)
			cnt++;
	}
	return (cnt);
}