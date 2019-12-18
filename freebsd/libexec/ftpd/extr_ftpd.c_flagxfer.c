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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  maskurg (int) ; 
 scalar_t__ recvurg ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int transflag ; 

__attribute__((used)) static void
flagxfer(int flag)
{

	if (flag) {
		if (transflag)
			syslog(LOG_ERR, "Internal: flagxfer(1): "
					"transfer already under way");
		transflag = 1;
		maskurg(0);
		recvurg = 0;
	} else {
		if (!transflag)
			syslog(LOG_ERR, "Internal: flagxfer(0): "
					"no active transfer");
		maskurg(1);
		transflag = 0;
	}
}