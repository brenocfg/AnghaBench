#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rmplen; int /*<<< orphan*/  rmp; } ;
typedef  TYPE_1__ RMPCONN ;

/* Variables and functions */
 int /*<<< orphan*/  BpfFd ; 
 int /*<<< orphan*/  EnetStr (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
BpfWrite(RMPCONN *rconn)
{
	if (write(BpfFd, (char *)&rconn->rmp, rconn->rmplen) < 0) {
		syslog(LOG_ERR, "write: %s: %m", EnetStr(rconn));
		return(0);
	}

	return(1);
}