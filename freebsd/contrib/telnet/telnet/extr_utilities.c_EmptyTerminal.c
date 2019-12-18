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
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ TTYBYTES () ; 
 int /*<<< orphan*/  select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ tout ; 
 int /*<<< orphan*/  ttyflush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
EmptyTerminal(void)
{
    fd_set	o;

    FD_ZERO(&o);

    if (TTYBYTES() == 0) {
	FD_SET(tout, &o);
	(void) select(tout+1, (fd_set *) 0, &o, (fd_set *) 0,
			(struct timeval *) 0);	/* wait for TTLOWAT */
    } else {
	while (TTYBYTES()) {
	    (void) ttyflush(0);
	    FD_SET(tout, &o);
	    (void) select(tout+1, (fd_set *) 0, &o, (fd_set *) 0,
				(struct timeval *) 0);	/* wait for TTLOWAT */
	}
    }
}