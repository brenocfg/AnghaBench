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
 int /*<<< orphan*/  ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_RESET ; 
 int PRIO_MAX ; 
 int PRIO_MIN ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 char const* bad_pri_value ; 
 char const* err_string () ; 
 int /*<<< orphan*/  errno ; 
 char* next_field (char*) ; 
 char const* no_proc_specified ; 
 int scanint (char*,int*) ; 
 int setpriority (int /*<<< orphan*/ ,int,int) ; 

const char *
renice_procs(char *str)
{
    char negate;
    int prio;
    int procnum;

    ERR_RESET;

    /* allow for negative priority values */
    if ((negate = (*str == '-')) != 0)
    {
	/* move past the minus sign */
	str++;
    }

    /* use procnum as a temporary holding place and get the number */
    procnum = scanint(str, &prio);

    /* negate if necessary */
    if (negate)
    {
	prio = -prio;
    }

    /* check for validity */
    if (procnum == -1 || prio < PRIO_MIN || prio > PRIO_MAX)
    {
	return(bad_pri_value);
    }

    /* move to the first process number */
    if ((str = next_field(str)) == NULL)
    {
	return(no_proc_specified);
    }

    /* loop thru the process numbers, renicing each one */
    do
    {
	if (scanint(str, &procnum) == -1)
	{
	    ERROR(str, 0);
	}

	if (setpriority(PRIO_PROCESS, procnum, prio) == -1)
	{
	    ERROR(str, errno);
	}
    } while ((str = next_field(str)) != NULL);

    /* return appropriate error string */
    return(err_string());
}