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
struct pwmbus_ivars {int pi_channel; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pwmbus_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int) ; 

__attribute__((used)) static int
pwmbus_child_location_str(device_t dev, device_t child, char *buf, size_t blen)
{
	struct pwmbus_ivars *ivars;

	ivars = device_get_ivars(child);
	snprintf(buf, blen, "hwdev=%s channel=%u", 
	    device_get_nameunit(device_get_parent(dev)), ivars->pi_channel);

	return (0);
}