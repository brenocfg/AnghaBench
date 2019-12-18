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
typedef  int /*<<< orphan*/  time_t ;
struct vrtc {int /*<<< orphan*/  vm; } ;
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_CTR1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_CTR2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VRTC_LOCK (struct vrtc*) ; 
 int /*<<< orphan*/  VRTC_UNLOCK (struct vrtc*) ; 
 int /*<<< orphan*/  sbinuptime () ; 
 struct vrtc* vm_rtc (struct vm*) ; 
 int vrtc_time_update (struct vrtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vrtc_set_time(struct vm *vm, time_t secs)
{
	struct vrtc *vrtc;
	int error;

	vrtc = vm_rtc(vm);
	VRTC_LOCK(vrtc);
	error = vrtc_time_update(vrtc, secs, sbinuptime());
	VRTC_UNLOCK(vrtc);

	if (error) {
		VM_CTR2(vrtc->vm, "Error %d setting RTC time to %#lx", error,
		    secs);
	} else {
		VM_CTR1(vrtc->vm, "RTC time set to %#lx", secs);
	}

	return (error);
}