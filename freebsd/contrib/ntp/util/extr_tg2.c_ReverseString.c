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
 int strlen (char*) ; 

void
ReverseString(char *str)
	{
	int		StringLength;
	int		IndexCounter;
	int		CentreOfString;
	char	TemporaryCharacter;


	StringLength	= strlen(str);
	CentreOfString	= (StringLength/2)+1;
	for (IndexCounter = StringLength; IndexCounter >= CentreOfString; IndexCounter--)
		{
		TemporaryCharacter				= str[IndexCounter-1];
		str[IndexCounter-1]				= str[StringLength-IndexCounter];
		str[StringLength-IndexCounter]	= TemporaryCharacter;
		}
	}