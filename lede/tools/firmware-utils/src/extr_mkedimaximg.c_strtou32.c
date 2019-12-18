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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ errno ; 
 unsigned int strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int strtou32(char *arg, unsigned int *val)
{
    char *endptr = NULL;

    errno = 0;
    *val = strtoul(arg, &endptr, 0);
    if (errno || (endptr == arg) || (*endptr && (endptr != NULL))) {
	return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}