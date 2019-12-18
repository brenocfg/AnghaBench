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
typedef  int uint32_t ;
struct vrtc {int addr; } ;
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VRTC_LOCK (struct vrtc*) ; 
 int /*<<< orphan*/  VRTC_UNLOCK (struct vrtc*) ; 
 struct vrtc* vm_rtc (struct vm*) ; 

int
vrtc_addr_handler(struct vm *vm, int vcpuid, bool in, int port, int bytes,
    uint32_t *val)
{
	struct vrtc *vrtc;

	vrtc = vm_rtc(vm);

	if (bytes != 1)
		return (-1);

	if (in) {
		*val = 0xff;
		return (0);
	}

	VRTC_LOCK(vrtc);
	vrtc->addr = *val & 0x7f;
	VRTC_UNLOCK(vrtc);

	return (0);
}