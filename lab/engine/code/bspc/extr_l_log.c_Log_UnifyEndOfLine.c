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
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

void Log_UnifyEndOfLine(char *buf)
{
	int i;

	for (i = 0; buf[i]; i++)
	{
		if (buf[i] == '\n')
		{
			if (i <= 0 || buf[i-1] != '\r')
			{
				memmove(&buf[i+1], &buf[i], strlen(&buf[i])+1);
				buf[i] = '\r';
				i++;
			} //end if
		} //end if
	} //end for
}