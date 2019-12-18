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
struct khash {int k_state; int /*<<< orphan*/  k_metric; int /*<<< orphan*/  k_mask; int /*<<< orphan*/  k_gate; int /*<<< orphan*/  k_dst; } ;

/* Variables and functions */
 int KS_DELETED ; 
 int KS_DYNAMIC ; 
#define  RTM_ADD 130 
#define  RTM_CHANGE 129 
#define  RTM_DELETE 128 
 int /*<<< orphan*/  rtioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
kern_ioctl(struct khash *k,
	   int action,			/* RTM_DELETE, etc */
	   int flags)

{
	switch (action) {
	case RTM_DELETE:
		k->k_state &= ~KS_DYNAMIC;
		if (k->k_state & KS_DELETED)
			return;
		k->k_state |= KS_DELETED;
		break;
	case RTM_ADD:
		k->k_state &= ~KS_DELETED;
		break;
	case RTM_CHANGE:
		if (k->k_state & KS_DELETED) {
			action = RTM_ADD;
			k->k_state &= ~KS_DELETED;
		}
		break;
	}

	rtioctl(action, k->k_dst, k->k_gate, k->k_mask, k->k_metric, flags);
}