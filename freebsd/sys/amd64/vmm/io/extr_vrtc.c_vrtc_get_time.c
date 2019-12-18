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
struct vrtc {int dummy; } ;
struct vm {int dummy; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  VRTC_LOCK (struct vrtc*) ; 
 int /*<<< orphan*/  VRTC_UNLOCK (struct vrtc*) ; 
 struct vrtc* vm_rtc (struct vm*) ; 
 int /*<<< orphan*/  vrtc_curtime (struct vrtc*,int /*<<< orphan*/ *) ; 

time_t
vrtc_get_time(struct vm *vm)
{
	struct vrtc *vrtc;
	sbintime_t basetime;
	time_t t;

	vrtc = vm_rtc(vm);
	VRTC_LOCK(vrtc);
	t = vrtc_curtime(vrtc, &basetime);
	VRTC_UNLOCK(vrtc);

	return (t);
}