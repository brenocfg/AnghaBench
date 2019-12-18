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
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 char* salloc (int) ; 
 int strlen (char*) ; 

char *
savestr(char *str)
{
	char *new;
	int size = strlen(str) + 1;

	if ((new = salloc(size)) != NULL)
		bcopy(str, new, size);
	return (new);
}