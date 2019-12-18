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
struct termios {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ handle_pending_signals () ; 
 int tcsetattr (int,int,struct termios const*) ; 

int
xtcsetattr(int fildes, int optional_actions, const struct termios *termios_p)
{
    int res;

    while ((res = tcsetattr(fildes, optional_actions, termios_p)) == -1 &&
	   errno == EINTR)
	if (handle_pending_signals())
	    break;
    return res;
}