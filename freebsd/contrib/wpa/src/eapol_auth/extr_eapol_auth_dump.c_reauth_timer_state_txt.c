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
#define  REAUTH_TIMER_INITIALIZE 129 
#define  REAUTH_TIMER_REAUTHENTICATE 128 

__attribute__((used)) static inline const char * reauth_timer_state_txt(int s)
{
	switch (s) {
	case REAUTH_TIMER_INITIALIZE: return "INITIALIZE";
	case REAUTH_TIMER_REAUTHENTICATE: return "REAUTHENTICATE";
	default: return "Unknown";
	}
}