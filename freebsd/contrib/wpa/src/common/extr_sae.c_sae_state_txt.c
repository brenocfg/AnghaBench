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
typedef  enum sae_state { ____Placeholder_sae_state } sae_state ;

/* Variables and functions */
#define  SAE_ACCEPTED 131 
#define  SAE_COMMITTED 130 
#define  SAE_CONFIRMED 129 
#define  SAE_NOTHING 128 

const char * sae_state_txt(enum sae_state state)
{
	switch (state) {
	case SAE_NOTHING:
		return "Nothing";
	case SAE_COMMITTED:
		return "Committed";
	case SAE_CONFIRMED:
		return "Confirmed";
	case SAE_ACCEPTED:
		return "Accepted";
	}
	return "?";
}