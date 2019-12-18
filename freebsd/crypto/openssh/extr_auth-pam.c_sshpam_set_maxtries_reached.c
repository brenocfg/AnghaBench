#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ challenge_response_authentication; scalar_t__ kbd_interactive_authentication; scalar_t__ password_authentication; } ;

/* Variables and functions */
 TYPE_1__ options ; 
 int sshpam_maxtries_reached ; 

void
sshpam_set_maxtries_reached(int reached)
{
	if (reached == 0 || sshpam_maxtries_reached)
		return;
	sshpam_maxtries_reached = 1;
	options.password_authentication = 0;
	options.kbd_interactive_authentication = 0;
	options.challenge_response_authentication = 0;
}