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
struct vmcb_segment {int dummy; } ;
struct vmcb {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bcopy (struct vmcb_segment*,struct vmcb_segment*,int) ; 
 struct vmcb_segment* vmcb_segptr (struct vmcb*,int) ; 

int
vmcb_seg(struct vmcb *vmcb, int ident, struct vmcb_segment *seg2)
{
	struct vmcb_segment *seg;

	seg = vmcb_segptr(vmcb, ident);
	if (seg != NULL) {
		bcopy(seg, seg2, sizeof(struct vmcb_segment));
		return (0);
	} else {
		return (EINVAL);
	}
}