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
#define  COMMIT 133 
#define  CONFIRM 132 
#define  FAILURE 131 
#define  FAILURE_REPORT 130 
#define  IDENTITY 129 
#define  SUCCESS 128 

__attribute__((used)) static const char * eap_eke_state_txt(int state)
{
	switch (state) {
	case IDENTITY:
		return "IDENTITY";
	case COMMIT:
		return "COMMIT";
	case CONFIRM:
		return "CONFIRM";
	case FAILURE_REPORT:
		return "FAILURE_REPORT";
	case SUCCESS:
		return "SUCCESS";
	case FAILURE:
		return "FAILURE";
	default:
		return "?";
	}
}