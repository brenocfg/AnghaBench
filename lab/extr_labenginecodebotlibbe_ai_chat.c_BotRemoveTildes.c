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

void BotRemoveTildes(char *message)
{
	int i;

	//remove all tildes from the chat message
	for (i = 0; message[i]; i++)
	{
		if (message[i] == '~')
		{
			memmove(&message[i], &message[i+1], strlen(&message[i+1])+1);
		} //end if
	} //end for
}