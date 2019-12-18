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
typedef  int /*<<< orphan*/  u32 ;
struct edid_quirk {scalar_t__ product_id; int /*<<< orphan*/  quirks; int /*<<< orphan*/  vendor; } ;
struct edid {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct edid_quirk*) ; 
 scalar_t__ EDID_PRODUCT_ID (struct edid*) ; 
 struct edid_quirk* edid_quirk_list ; 
 scalar_t__ edid_vendor (struct edid*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 edid_get_quirks(struct edid *edid)
{
	struct edid_quirk *quirk;
	int i;

	for (i = 0; i < ARRAY_SIZE(edid_quirk_list); i++) {
		quirk = &edid_quirk_list[i];

		if (edid_vendor(edid, quirk->vendor) &&
		    (EDID_PRODUCT_ID(edid) == quirk->product_id))
			return quirk->quirks;
	}

	return 0;
}