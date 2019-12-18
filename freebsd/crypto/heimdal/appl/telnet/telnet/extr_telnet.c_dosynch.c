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
 int /*<<< orphan*/  DM ; 
 int /*<<< orphan*/  IAC ; 
 int /*<<< orphan*/  NETADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netclear () ; 
 int /*<<< orphan*/  printoption (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setneturg () ; 

int
dosynch()
{
    netclear();			/* clear the path to the network */
    NETADD(IAC);
    setneturg();
    NETADD(DM);
    printoption("SENT", IAC, DM);
    return 1;
}