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
typedef  int devinfo_state_t ;

/* Variables and functions */
#define  DS_ALIVE 131 
#define  DS_ATTACHED 130 
#define  DS_BUSY 129 
#define  DS_NOTPRESENT 128 

__attribute__((used)) static const char *
devstate(devinfo_state_t state)
{
	switch (state) {
	case DS_NOTPRESENT:
		return "not-present";
	case DS_ALIVE:
		return "alive";
	case DS_ATTACHED:
		return "attached";
	case DS_BUSY:
		return "busy";
	default:
		return "unknown-state";
	}
}