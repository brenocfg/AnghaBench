#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sigcontext {int dummy; } ;
struct TYPE_3__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ adjtime (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  adjustment ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__ result ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int (*) (int,int,struct sigcontext*)) ; 

int
timeout(
	int sig,
	int code,
	struct sigcontext *scp
	)
{
	signal (SIGALRM, timeout);
	if (adjtime(&adjustment, &result)) 
	    printf("adjtime call failed\n");
	if (result.tv_sec != 0 || result.tv_usec != 0) {
		printf("result.u = %d.%06.6d  ", (int) result.tv_sec,
		       (int) result.tv_usec);
	}
}