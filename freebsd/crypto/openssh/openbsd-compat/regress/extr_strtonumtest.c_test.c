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
 int fail ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 long long strtonum (char const*,long long,long long,char const**) ; 

void
test(const char *p, long long lb, long long ub, int ok)
{
	long long val;
	const char *q;

	val = strtonum(p, lb, ub, &q);
	if (ok && q != NULL) {
		fprintf(stderr, "%s [%lld-%lld] ", p, lb, ub);
		fprintf(stderr, "NUMBER NOT ACCEPTED %s\n", q);
		fail = 1;
	} else if (!ok && q == NULL) {
		fprintf(stderr, "%s [%lld-%lld] %lld ", p, lb, ub, val);
		fprintf(stderr, "NUMBER ACCEPTED\n");
		fail = 1;
	}
}