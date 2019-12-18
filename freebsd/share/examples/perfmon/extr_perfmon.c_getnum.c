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
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getnum(const char *buf, int min, int max)
{
	char *ep;
	long l;

	errno = 0;
	l = strtol(buf, &ep, 0);
	if (*buf && !*ep && !errno) {
		if (l < min || l > max) {
			errx(1, "%s: must be between %d and %d", 
			     buf, min, max);
		}
		return (int)l;
	} 

	errx(1, "%s: parameter must be an integer", buf);
}