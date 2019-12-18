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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ time_t ;
struct rtcdev {int reg_c; } ;
struct vrtc {int addr; struct rtcdev rtcdev; } ;
struct vm {int dummy; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int RTC_CENTURY ; 
 int /*<<< orphan*/  VCPU_CTR1 (struct vm*,int,char*,int) ; 
 int /*<<< orphan*/  VCPU_CTR2 (struct vm*,int,char*,int,int) ; 
 scalar_t__ VRTC_BROKEN_TIME ; 
 int /*<<< orphan*/  VRTC_LOCK (struct vrtc*) ; 
 int /*<<< orphan*/  VRTC_UNLOCK (struct vrtc*) ; 
 scalar_t__ rtc_flag_broken_time ; 
 int /*<<< orphan*/  rtc_halted (struct vrtc*) ; 
 scalar_t__ rtc_to_secs (struct vrtc*) ; 
 int /*<<< orphan*/  sbinuptime () ; 
 int /*<<< orphan*/  secs_to_rtc (scalar_t__,struct vrtc*,int /*<<< orphan*/ ) ; 
 struct vrtc* vm_rtc (struct vm*) ; 
 scalar_t__ vrtc_curtime (struct vrtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrtc_set_reg_a (struct vrtc*,int) ; 
 int vrtc_set_reg_b (struct vrtc*,int) ; 
 int /*<<< orphan*/  vrtc_set_reg_c (struct vrtc*,int /*<<< orphan*/ ) ; 
 int vrtc_time_update (struct vrtc*,scalar_t__,int /*<<< orphan*/ ) ; 

int
vrtc_data_handler(struct vm *vm, int vcpuid, bool in, int port, int bytes,
    uint32_t *val)
{
	struct vrtc *vrtc;
	struct rtcdev *rtc;
	sbintime_t basetime;
	time_t curtime;
	int error, offset;

	vrtc = vm_rtc(vm);
	rtc = &vrtc->rtcdev;

	if (bytes != 1)
		return (-1);

	VRTC_LOCK(vrtc);
	offset = vrtc->addr;
	if (offset >= sizeof(struct rtcdev)) {
		VRTC_UNLOCK(vrtc);
		return (-1);
	}

	error = 0;
	curtime = vrtc_curtime(vrtc, &basetime);
	vrtc_time_update(vrtc, curtime, basetime);

	/*
	 * Update RTC date/time fields if necessary.
	 *
	 * This is not just for reads of the RTC. The side-effect of writing
	 * the century byte requires other RTC date/time fields (e.g. sec)
	 * to be updated here.
	 */
	if (offset < 10 || offset == RTC_CENTURY)
		secs_to_rtc(curtime, vrtc, 0);

	if (in) {
		if (offset == 12) {
			/*
			 * XXX
			 * reg_c interrupt flags are updated only if the
			 * corresponding interrupt enable bit in reg_b is set.
			 */
			*val = vrtc->rtcdev.reg_c;
			vrtc_set_reg_c(vrtc, 0);
		} else {
			*val = *((uint8_t *)rtc + offset);
		}
		VCPU_CTR2(vm, vcpuid, "Read value %#x from RTC offset %#x",
		    *val, offset);
	} else {
		switch (offset) {
		case 10:
			VCPU_CTR1(vm, vcpuid, "RTC reg_a set to %#x", *val);
			vrtc_set_reg_a(vrtc, *val);
			break;
		case 11:
			VCPU_CTR1(vm, vcpuid, "RTC reg_b set to %#x", *val);
			error = vrtc_set_reg_b(vrtc, *val);
			break;
		case 12:
			VCPU_CTR1(vm, vcpuid, "RTC reg_c set to %#x (ignored)",
			    *val);
			break;
		case 13:
			VCPU_CTR1(vm, vcpuid, "RTC reg_d set to %#x (ignored)",
			    *val);
			break;
		case 0:
			/*
			 * High order bit of 'seconds' is readonly.
			 */
			*val &= 0x7f;
			/* FALLTHRU */
		default:
			VCPU_CTR2(vm, vcpuid, "RTC offset %#x set to %#x",
			    offset, *val);
			*((uint8_t *)rtc + offset) = *val;
			break;
		}

		/*
		 * XXX some guests (e.g. OpenBSD) write the century byte
		 * outside of RTCSB_HALT so re-calculate the RTC date/time.
		 */
		if (offset == RTC_CENTURY && !rtc_halted(vrtc)) {
			curtime = rtc_to_secs(vrtc);
			error = vrtc_time_update(vrtc, curtime, sbinuptime());
			KASSERT(!error, ("vrtc_time_update error %d", error));
			if (curtime == VRTC_BROKEN_TIME && rtc_flag_broken_time)
				error = -1;
		}
	}
	VRTC_UNLOCK(vrtc);
	return (error);
}