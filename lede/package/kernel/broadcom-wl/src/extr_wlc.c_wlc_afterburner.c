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
typedef  int wlc_param ;

/* Variables and functions */
 int GET ; 
 int PARAM_MODE ; 
 int /*<<< orphan*/  interface ; 
 int wl_iovar_get (int /*<<< orphan*/ ,char*,int*,int) ; 
 int wl_iovar_setint (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int wlc_afterburner(wlc_param param, void *data, void *value)
{
	int *val = (int *) value;
	int ret = 0;

	if ((param & PARAM_MODE) == GET) {
		ret = wl_iovar_get(interface, "afterburner", val, sizeof(int));
	} else {
		wl_iovar_setint(interface, "wlfeatureflag", (*val ? 3 : 0));
		ret = wl_iovar_setint(interface, "afterburner", (*val ? 1 : 0));
		wl_iovar_setint(interface, "afterburner_override", *val);
	}

	return ret;
}