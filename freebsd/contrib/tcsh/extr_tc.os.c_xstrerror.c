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
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 char** sys_errlist ; 
 int sys_nerr ; 
 char* xasprintf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 

char *
xstrerror(int i)
{
    if (i >= 0 && i < sys_nerr) {
	return sys_errlist[i];
    } else {
	static char *errbuf; /* = NULL; */

	xfree(errbuf);
	errbuf = xasprintf(CGETS(23, 13, "Unknown Error: %d"), i);
	return errbuf;
    }
}