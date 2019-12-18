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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,long long,long long,long long,long long) ; 

__attribute__((used)) static void dump_cqe(void *arg)
{
	u64 *p = arg;
	syslog(LOG_NOTICE, "cxgb4 err cqe %016llx %016llx %016llx %016llx\n",
	       (long long)be64toh(p[0]),
	       (long long)be64toh(p[1]),
	       (long long)be64toh(p[2]),
	       (long long)be64toh(p[3]));
}