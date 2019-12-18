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
#define  CHALLENGE 133 
#define  FAILURE 132 
#define  NOTIFICATION 131 
#define  REAUTH 130 
#define  START 129 
#define  SUCCESS 128 

__attribute__((used)) static const char * eap_sim_state_txt(int state)
{
	switch (state) {
	case START:
		return "START";
	case CHALLENGE:
		return "CHALLENGE";
	case REAUTH:
		return "REAUTH";
	case SUCCESS:
		return "SUCCESS";
	case FAILURE:
		return "FAILURE";
	case NOTIFICATION:
		return "NOTIFICATION";
	default:
		return "Unknown?!";
	}
}