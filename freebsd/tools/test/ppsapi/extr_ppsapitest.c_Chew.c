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
struct timespec {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ uflag ; 

__attribute__((used)) static void
Chew(struct timespec *tsa, struct timespec *tsc, unsigned sa, unsigned sc)
{
	printf("%jd .%09ld %u", (intmax_t)tsa->tv_sec, tsa->tv_nsec, sa);
	printf(" %jd .%09ld %u\n", (intmax_t)tsc->tv_sec, tsc->tv_nsec, sc);
	if (uflag)
		fflush(stdout);
}