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
 scalar_t__ EINTR ; 
 int close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ handle_pending_signals () ; 

void
xclose(int fildes)
{
    if (fildes < 0)
	return;
    while (close(fildes) == -1 && errno == EINTR)
	if (handle_pending_signals())
	    break;
}