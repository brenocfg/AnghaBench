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
#define  CHALLENGE 132 
#define  CONFIRM 131 
#define  FAILURE 130 
#define  IDENTITY 129 
#define  SUCCESS 128 

__attribute__((used)) static const char * eap_sake_state_txt(int state)
{
	switch (state) {
	case IDENTITY:
		return "IDENTITY";
	case CHALLENGE:
		return "CHALLENGE";
	case CONFIRM:
		return "CONFIRM";
	case SUCCESS:
		return "SUCCESS";
	case FAILURE:
		return "FAILURE";
	default:
		return "?";
	}
}