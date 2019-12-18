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
typedef  int uint16_t ;
struct evdev_dev {int /*<<< orphan*/  ev_sw_flags; int /*<<< orphan*/  ev_snd_flags; int /*<<< orphan*/  ev_led_flags; int /*<<< orphan*/  ev_msc_flags; int /*<<< orphan*/  ev_abs_flags; int /*<<< orphan*/ * ev_mt; int /*<<< orphan*/  ev_rel_flags; int /*<<< orphan*/  ev_key_flags; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int ABS_CNT ; 
 int /*<<< orphan*/  ABS_IS_MT (int) ; 
 int ABS_MT_SLOT ; 
 int EINVAL ; 
#define  EV_ABS 136 
 int EV_CNT ; 
#define  EV_KEY 135 
#define  EV_LED 134 
#define  EV_MSC 133 
#define  EV_REL 132 
#define  EV_REP 131 
#define  EV_SND 130 
#define  EV_SW 129 
#define  EV_SYN 128 
 int KEY_CNT ; 
 int LED_CNT ; 
 int /*<<< orphan*/  MAXIMAL_MT_SLOT (struct evdev_dev*) ; 
 int MSC_CNT ; 
 int REL_CNT ; 
 int REP_CNT ; 
 int SND_CNT ; 
 int SW_CNT ; 
 int SYN_CNT ; 
 int /*<<< orphan*/  bit_test (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evdev_event_supported (struct evdev_dev*,int) ; 

__attribute__((used)) static int
evdev_check_event(struct evdev_dev *evdev, uint16_t type, uint16_t code,
    int32_t value)
{

	if (type >= EV_CNT)
		return (EINVAL);

	/* Allow SYN events implicitly */
	if (type != EV_SYN && !evdev_event_supported(evdev, type))
		return (EINVAL);

	switch (type) {
	case EV_SYN:
		if (code >= SYN_CNT)
			return (EINVAL);
		break;

	case EV_KEY:
		if (code >= KEY_CNT)
			return (EINVAL);
		if (!bit_test(evdev->ev_key_flags, code))
			return (EINVAL);
		break;

	case EV_REL:
		if (code >= REL_CNT)
			return (EINVAL);
		if (!bit_test(evdev->ev_rel_flags, code))
			return (EINVAL);
		break;

	case EV_ABS:
		if (code >= ABS_CNT)
			return (EINVAL);
		if (!bit_test(evdev->ev_abs_flags, code))
			return (EINVAL);
		if (code == ABS_MT_SLOT &&
		    (value < 0 || value > MAXIMAL_MT_SLOT(evdev)))
			return (EINVAL);
		if (ABS_IS_MT(code) && evdev->ev_mt == NULL &&
		    bit_test(evdev->ev_abs_flags, ABS_MT_SLOT))
			return (EINVAL);
		break;

	case EV_MSC:
		if (code >= MSC_CNT)
			return (EINVAL);
		if (!bit_test(evdev->ev_msc_flags, code))
			return (EINVAL);
		break;

	case EV_LED:
		if (code >= LED_CNT)
			return (EINVAL);
		if (!bit_test(evdev->ev_led_flags, code))
			return (EINVAL);
		break;

	case EV_SND:
		if (code >= SND_CNT)
			return (EINVAL);
		if (!bit_test(evdev->ev_snd_flags, code))
			return (EINVAL);
		break;

	case EV_SW:
		if (code >= SW_CNT)
			return (EINVAL);
		if (!bit_test(evdev->ev_sw_flags, code))
			return (EINVAL);
		break;

	case EV_REP:
		if (code >= REP_CNT)
			return (EINVAL);
		break;

	default:
		return (EINVAL);
	}

	return (0);
}