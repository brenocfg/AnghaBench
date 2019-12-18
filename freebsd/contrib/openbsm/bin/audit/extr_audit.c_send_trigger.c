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
 int EPERM ; 
 int audit_send_trigger (int*) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int
send_trigger(int trigger)
{
	int error;

	error = audit_send_trigger(&trigger);
	if (error != 0) {
		if (error == EPERM)
			perror("audit requires root privileges");
		else
			perror("Error sending trigger");
		return (-1);
	}

	return (0);
}