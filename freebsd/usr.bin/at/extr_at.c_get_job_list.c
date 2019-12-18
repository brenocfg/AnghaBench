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
 long* malloc (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static long *
get_job_list(int argc, char *argv[], int *joblen)
{
    int i, len;
    long *joblist;
    char *ep;

    joblist = NULL;
    len = argc;
    if (len > 0) {
	if ((joblist = malloc(len * sizeof(*joblist))) == NULL)
	    panic("out of memory");

	for (i = 0; i < argc; i++) {
	    errno = 0;
	    if ((joblist[i] = strtol(argv[i], &ep, 10)) < 0 ||
		ep == argv[i] || *ep != '\0' || errno)
		panic("invalid job number");
	}
    }

    *joblen = len;
    return joblist;
}