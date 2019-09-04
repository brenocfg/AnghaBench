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

__attribute__((used)) static char *outd(long n, FILE *f, char *bp) {
	unsigned long m;
	char buf[25], *s = buf + sizeof buf;

	*--s = '\0';
	if (n < 0)
		m = -n;
	else
		m = n;
	do
		*--s = m%10 + '0';
	while ((m /= 10) != 0);
	if (n < 0)
		*--s = '-';
	return outs(s, f, bp);
}