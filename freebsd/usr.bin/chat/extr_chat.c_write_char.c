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
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ alarmed ; 
 int /*<<< orphan*/  chat_logf (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ put_char (int) ; 
 scalar_t__ verbose ; 

int
write_char(int c)
{
    if (alarmed || put_char(c) < 0) {
	alarm(0);
	alarmed = 0;

	if (verbose) {
	    if (errno == EINTR || errno == EWOULDBLOCK)
		chat_logf(" -- write timed out");
	    else
		chat_logf(" -- write failed: %m");
	}
	return (0);
    }
    return (1);
}