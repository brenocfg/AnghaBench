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

/* Variables and functions */
#define  FAILURE 131 
#define  GPSK_1 130 
#define  GPSK_3 129 
#define  SUCCESS 128 

__attribute__((used)) static const char * eap_gpsk_state_txt(int state)
{
	switch (state) {
	case GPSK_1:
		return "GPSK-1";
	case GPSK_3:
		return "GPSK-3";
	case SUCCESS:
		return "SUCCESS";
	case FAILURE:
		return "FAILURE";
	default:
		return "?";
	}
}