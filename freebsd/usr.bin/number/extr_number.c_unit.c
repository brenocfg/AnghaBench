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
 scalar_t__ lflag ; 
 char** name3 ; 
 scalar_t__ number (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
unit(int len, char *p)
{
	int off, rval;

	rval = 0;
	if (len > 3) {
		if (len % 3) {
			off = len % 3;
			len -= off;
			if (number(p, off)) {
				rval = 1;
				(void)printf(" %s%s",
				    name3[len / 3], lflag ? " " : ".\n");
			}
			p += off;
		}
		for (; len > 3; p += 3) {
			len -= 3;
			if (number(p, 3)) {
				rval = 1;
				(void)printf(" %s%s",
				    name3[len / 3], lflag ? " " : ".\n");
			}
		}
	}
	if (number(p, len)) {
		if (!lflag)
			(void)printf(".\n");
		rval = 1;
	}
	return (rval);
}