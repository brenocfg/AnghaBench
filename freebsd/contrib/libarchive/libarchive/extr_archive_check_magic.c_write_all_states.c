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
 char* state_name (unsigned int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static char *
write_all_states(char *buff, unsigned int states)
{
	unsigned int lowbit;

	buff[0] = '\0';

	/* A trick for computing the lowest set bit. */
	while ((lowbit = states & (1 + ~states)) != 0) {
		states &= ~lowbit;		/* Clear the low bit. */
		strcat(buff, state_name(lowbit));
		if (states != 0)
			strcat(buff, "/");
	}
	return buff;
}