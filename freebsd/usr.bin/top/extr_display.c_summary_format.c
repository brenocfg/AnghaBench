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
typedef  int /*<<< orphan*/  rbuf ;

/* Variables and functions */
 char const* format_k (int) ; 
 char const* itoa (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,float) ; 
 char* stpcpy (char*,char const*) ; 

__attribute__((used)) static void
summary_format(char *str, int *numbers, const char * const *names)
{
    char *p;
    int num;
    const char *thisname;
    char rbuf[6];

    /* format each number followed by its string */
    p = str;
    while ((thisname = *names++) != NULL)
    {
	/* get the number to format */
	num = *numbers++;

	/* display only non-zero numbers */
	if (num > 0)
	{
	    /* is this number in kilobytes? */
	    if (thisname[0] == 'K')
	    {
		/* yes: format it as a memory value */
		p = stpcpy(p, format_k(num));

		/* skip over the K, since it was included by format_k */
		p = stpcpy(p, thisname+1);
	    }
	    /* is this number a ratio? */
	    else if (thisname[0] == ':')
	    {
		(void) snprintf(rbuf, sizeof(rbuf), "%.2f",
		    (float)*(numbers - 2) / (float)num);
		p = stpcpy(p, rbuf);
		p = stpcpy(p, thisname);
	    }
	    else
	    {
		p = stpcpy(p, itoa(num));
		p = stpcpy(p, thisname);
	    }
	}

	/* ignore negative numbers, but display corresponding string */
	else if (num < 0)
	{
	    p = stpcpy(p, thisname);
	}
    }

    /* if the last two characters in the string are ", ", delete them */
    p -= 2;
    if (p >= str && p[0] == ',' && p[1] == ' ')
    {
	*p = '\0';
    }
}