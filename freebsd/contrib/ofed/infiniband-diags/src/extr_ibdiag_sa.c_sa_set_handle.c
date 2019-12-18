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
struct TYPE_2__ {int grh_present; int /*<<< orphan*/  gid; } ;
struct sa_handle {TYPE_1__ dport; } ;
typedef  int /*<<< orphan*/  ibmad_gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int sa_set_handle(struct sa_handle * handle, int grh_present, ibmad_gid_t *gid)
{
	if (grh_present) {
		if (gid == NULL) {
			return -1;
		} else {
			handle->dport.grh_present = 1;
			memcpy(handle->dport.gid, gid, 16);
		}
	}
	return 0;
}