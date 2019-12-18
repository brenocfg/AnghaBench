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
typedef  int /*<<< orphan*/  u_int ;
struct pwmbus_ivars {int /*<<< orphan*/  pi_channel; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PWMBUS_IVAR_CHANNEL 128 
 struct pwmbus_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pwmbus_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct pwmbus_ivars *ivars;

	ivars = device_get_ivars(child);

	switch (which) {
	case PWMBUS_IVAR_CHANNEL:
		*(u_int *)result = ivars->pi_channel;
		break;
	default:
		return (EINVAL);
	}

	return (0);
}