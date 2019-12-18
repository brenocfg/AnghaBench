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
typedef  int uint32_t ;

/* Variables and functions */
 int REQ ; 
#define  RESP 128 
 int be_state ; 
 int /*<<< orphan*/  fwctl_response (int*) ; 

__attribute__((used)) static uint32_t
fwctl_inl(void)
{
	uint32_t retval;

	switch (be_state) {
	case RESP:
		if (fwctl_response(&retval))
			be_state = REQ;
		break;
	default:
		retval = 0xffffffff;
		break;
	}

	return (retval);
}