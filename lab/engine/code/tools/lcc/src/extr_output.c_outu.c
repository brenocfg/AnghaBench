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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* outs (char*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char *outu(unsigned long n, int base, FILE *f, char *bp) {
	char buf[25], *s = buf + sizeof buf;

	*--s = '\0';
	do
		*--s = "0123456789abcdef"[n%base];
	while ((n /= base) != 0);
	return outs(s, f, bp);
}