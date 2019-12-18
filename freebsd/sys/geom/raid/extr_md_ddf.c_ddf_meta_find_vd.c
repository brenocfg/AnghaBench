#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ddf_meta {TYPE_2__* vdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  Populated_VDEs; int /*<<< orphan*/  Max_VDE_Supported; } ;
struct TYPE_5__ {TYPE_1__* entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  VD_GUID; } ;

/* Variables and functions */
 int GET16 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET16 (struct ddf_meta*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ isff (int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* vdr ; 

__attribute__((used)) static int
ddf_meta_find_vd(struct ddf_meta *meta, uint8_t *GUID)
{
	int i;

	for (i = 0; i < GET16(meta, vdr->Populated_VDEs); i++) {
		if (GUID != NULL) {
			if (memcmp(meta->vdr->entry[i].VD_GUID, GUID, 24) == 0)
				return (i);
		} else
			if (isff(meta->vdr->entry[i].VD_GUID, 24))
				return (i);
	}
	if (GUID == NULL) {
		if (i >= GET16(meta, vdr->Max_VDE_Supported))
			return (-1);
		SET16(meta, vdr->Populated_VDEs, i + 1);
		return (i);
	}
	return (-1);
}