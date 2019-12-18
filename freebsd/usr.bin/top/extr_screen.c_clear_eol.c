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
 scalar_t__ clear_line ; 
 int /*<<< orphan*/  overstrike ; 
 int /*<<< orphan*/  putcap (scalar_t__) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ smart_terminal ; 

int
clear_eol(int len)
{
    if (smart_terminal && !overstrike && len > 0)
    {
	if (clear_line)
	{
	    putcap(clear_line);
	    return(0);
	}
	else
	{
	    while (len-- > 0)
	    {
		putchar(' ');
	    }
	    return(1);
	}
    }
    return(-1);
}