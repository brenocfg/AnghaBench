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
struct kvmppc_vpa {scalar_t__ next_gpa; int /*<<< orphan*/ * pinned_addr; scalar_t__ update_pending; } ;

/* Variables and functions */

__attribute__((used)) static int vpa_is_registered(struct kvmppc_vpa *vpap)
{
	if (vpap->update_pending)
		return vpap->next_gpa != 0;
	return vpap->pinned_addr != NULL;
}