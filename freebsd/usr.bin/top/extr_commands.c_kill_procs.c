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
 int NSIG ; 
 int SIGTERM ; 
 char const* bad_signal_name ; 
 char const* err_string () ; 
 int /*<<< orphan*/  errno ; 
 char const* invalid_signal_number ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ isspace (char) ; 
 int kill (int,int) ; 
 char* next_field (char*) ; 
 char const* no_proc_specified ; 
 int scanint (char*,int*) ; 
 int signame_to_signum (char*) ; 

const char *
kill_procs(char *str)
{
    char *nptr;
    int signum = SIGTERM;	/* default */
    int procnum;

    /* reset error array */
    ERR_RESET;

    /* skip over leading white space */
    while (isspace(*str)) str++;

    if (str[0] == '-')
    {
	/* explicit signal specified */
	if ((nptr = next_field(str)) == NULL)
	{
	    return(no_proc_specified);
	}

	if (isdigit(str[1]))
	{
	    scanint(str + 1, &signum);
	    if (signum <= 0 || signum >= NSIG)
	    {
		return(invalid_signal_number);
	    }
	}
	else
	{
		signum = signame_to_signum(str + 1);

	    /* was it ever found */
	    if (signum == -1 )
	    {
			return(bad_signal_name);
	    }
	}
	/* put the new pointer in place */
	str = nptr;
    }

    /* loop thru the string, killing processes */
    do
    {
	if (scanint(str, &procnum) == -1)
	{
	    ERROR(str, 0);
	}
	else
	{
	    /* go in for the kill */
	    if (kill(procnum, signum) == -1)
	    {
		/* chalk up an error */
		ERROR(str, errno);
	    }
	}
    } while ((str = next_field(str)) != NULL);

    /* return appropriate error string */
    return(err_string());
}