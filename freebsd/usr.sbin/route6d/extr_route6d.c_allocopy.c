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
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
allocopy(char *p)
{
	int len = strlen(p) + 1;
	char *q = (char *)malloc(len);

	if (!q) {
		fatal("malloc");
		/*NOTREACHED*/
	}

	strlcpy(q, p, len);
	return q;
}