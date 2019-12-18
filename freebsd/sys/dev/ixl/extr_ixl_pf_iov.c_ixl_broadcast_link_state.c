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
struct ixl_pf {int num_vfs; int /*<<< orphan*/ * vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixl_notify_vf_link_state (struct ixl_pf*,int /*<<< orphan*/ *) ; 

void
ixl_broadcast_link_state(struct ixl_pf *pf)
{
	int i;

	for (i = 0; i < pf->num_vfs; i++)
		ixl_notify_vf_link_state(pf, &pf->vfs[i]);
}