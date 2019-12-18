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
#define  SIGUSR1 129 
#define  SIGUSR2 128 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int /*<<< orphan*/  rate_get ; 
 int /*<<< orphan*/  rate_get_incr ; 
 int /*<<< orphan*/  rate_put ; 
 int /*<<< orphan*/  rate_put_incr ; 

void
crankrate(int sig)
{

	switch (sig) {
	case SIGUSR1:
		if (rate_get)
			rate_get += rate_get_incr;
		if (rate_put)
			rate_put += rate_put_incr;
		break;
	case SIGUSR2:
		if (rate_get && rate_get > rate_get_incr)
			rate_get -= rate_get_incr;
		if (rate_put && rate_put > rate_put_incr)
			rate_put -= rate_put_incr;
		break;
	default:
		err(1, "crankrate invoked with unknown signal: %d", sig);
	}
}