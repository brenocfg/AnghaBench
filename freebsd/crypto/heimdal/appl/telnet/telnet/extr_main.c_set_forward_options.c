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
 int forward_option ; 
 int /*<<< orphan*/  kerberos5_set_forward (int) ; 
 int /*<<< orphan*/  kerberos5_set_forwardable (int) ; 

void
set_forward_options(void)
{
#ifdef FORWARD
	switch(forward_option) {
	case 'f':
		kerberos5_set_forward(1);
		kerberos5_set_forwardable(0);
		break;
	case 'F':
		kerberos5_set_forward(1);
		kerberos5_set_forwardable(1);
		break;
	case 'G':
		kerberos5_set_forward(0);
		kerberos5_set_forwardable(0);
		break;
	default:
		break;
	}
#endif
}