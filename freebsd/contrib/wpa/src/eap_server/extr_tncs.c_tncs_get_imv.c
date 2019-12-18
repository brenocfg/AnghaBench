#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tnc_if_imv {scalar_t__ imvID; struct tnc_if_imv* next; } ;
struct TYPE_2__ {struct tnc_if_imv* imv; } ;
typedef  scalar_t__ TNC_IMVID ;

/* Variables and functions */
 scalar_t__ TNC_MAX_IMV_ID ; 
 TYPE_1__* tncs_global_data ; 

__attribute__((used)) static struct tnc_if_imv * tncs_get_imv(TNC_IMVID imvID)
{
	struct tnc_if_imv *imv;

	if (imvID >= TNC_MAX_IMV_ID || tncs_global_data == NULL)
		return NULL;
	imv = tncs_global_data->imv;
	while (imv) {
		if (imv->imvID == imvID)
			return imv;
		imv = imv->next;
	}
	return NULL;
}