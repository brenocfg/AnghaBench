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
struct vrtc {int /*<<< orphan*/  callout; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ callout_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void
vrtc_callout_check(struct vrtc *vrtc, sbintime_t freq)
{
	int active;

	active = callout_active(&vrtc->callout) ? 1 : 0;
	KASSERT((freq == 0 && !active) || (freq != 0 && active),
	    ("vrtc callout %s with frequency %#lx",
	    active ? "active" : "inactive", freq));
}