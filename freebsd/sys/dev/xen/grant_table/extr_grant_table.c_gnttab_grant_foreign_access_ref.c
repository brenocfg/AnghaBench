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
typedef  size_t grant_ref_t ;
typedef  int /*<<< orphan*/  domid_t ;
struct TYPE_2__ {unsigned long frame; int flags; int /*<<< orphan*/  domid; } ;

/* Variables and functions */
 int GTF_permit_access ; 
 int GTF_readonly ; 
 TYPE_1__* shared ; 
 int /*<<< orphan*/  wmb () ; 

void
gnttab_grant_foreign_access_ref(grant_ref_t ref, domid_t domid,
				unsigned long frame, int readonly)
{

	shared[ref].frame = frame;
	shared[ref].domid = domid;
	wmb();
	shared[ref].flags = GTF_permit_access | (readonly ? GTF_readonly : 0);
}