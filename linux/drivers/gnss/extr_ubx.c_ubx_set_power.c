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
struct gnss_serial {int dummy; } ;
typedef  enum gnss_serial_pm_state { ____Placeholder_gnss_serial_pm_state } gnss_serial_pm_state ;

/* Variables and functions */
 int EINVAL ; 
#define  GNSS_SERIAL_ACTIVE 130 
#define  GNSS_SERIAL_OFF 129 
#define  GNSS_SERIAL_STANDBY 128 
 int ubx_set_active (struct gnss_serial*) ; 
 int ubx_set_standby (struct gnss_serial*) ; 

__attribute__((used)) static int ubx_set_power(struct gnss_serial *gserial,
				enum gnss_serial_pm_state state)
{
	switch (state) {
	case GNSS_SERIAL_ACTIVE:
		return ubx_set_active(gserial);
	case GNSS_SERIAL_OFF:
	case GNSS_SERIAL_STANDBY:
		return ubx_set_standby(gserial);
	}

	return -EINVAL;
}