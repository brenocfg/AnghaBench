#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct hostapd_hw_modes {int num_channels; TYPE_1__* channels; } ;
typedef  enum chan_allowed { ____Placeholder_chan_allowed } chan_allowed ;
struct TYPE_2__ {scalar_t__ chan; int flag; } ;

/* Variables and functions */
 int ALLOWED ; 
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_NO_IR ; 
 int NOT_ALLOWED ; 
 int NO_IR ; 

__attribute__((used)) static enum chan_allowed allow_channel(struct hostapd_hw_modes *mode, u8 chan,
				       unsigned int *flags)
{
	int i;

	for (i = 0; i < mode->num_channels; i++) {
		if (mode->channels[i].chan == chan)
			break;
	}

	if (i == mode->num_channels ||
	    (mode->channels[i].flag & HOSTAPD_CHAN_DISABLED))
		return NOT_ALLOWED;

	if (flags)
		*flags = mode->channels[i].flag;

	if (mode->channels[i].flag & HOSTAPD_CHAN_NO_IR)
		return NO_IR;

	return ALLOWED;
}