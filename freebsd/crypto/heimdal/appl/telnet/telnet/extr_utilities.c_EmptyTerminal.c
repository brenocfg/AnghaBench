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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  ExitString (char*,int) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ TTYBYTES () ; 
 int /*<<< orphan*/  select (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timeval*) ; 
 scalar_t__ tout ; 
 int /*<<< orphan*/  ttyflush (int /*<<< orphan*/ ) ; 

void
EmptyTerminal(void)
{
    fd_set	outs;

    FD_ZERO(&outs);

    if (tout >= FD_SETSIZE)
	ExitString("fd too large", 1);

    if (TTYBYTES() == 0) {
	FD_SET(tout, &outs);
	select(tout+1, 0, &outs, 0,
		      (struct timeval *) 0); /* wait for TTLOWAT */
    } else {
	while (TTYBYTES()) {
	    ttyflush(0);
	    FD_SET(tout, &outs);
	    select(tout+1, 0, &outs, 0,
			  (struct timeval *) 0); /* wait for TTLOWAT */
	}
    }
}