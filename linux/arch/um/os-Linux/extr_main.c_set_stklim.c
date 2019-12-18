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
struct rlimit {scalar_t__ rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_STACK ; 
 scalar_t__ RLIM_INFINITY ; 
 scalar_t__ STACKSIZE ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

__attribute__((used)) static void set_stklim(void)
{
	struct rlimit lim;

	if (getrlimit(RLIMIT_STACK, &lim) < 0) {
		perror("getrlimit");
		exit(1);
	}
	if ((lim.rlim_cur == RLIM_INFINITY) || (lim.rlim_cur > STACKSIZE)) {
		lim.rlim_cur = STACKSIZE;
		if (setrlimit(RLIMIT_STACK, &lim) < 0) {
			perror("setrlimit");
			exit(1);
		}
	}
}