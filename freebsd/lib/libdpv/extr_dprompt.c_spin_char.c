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
 int SPIN_SIZE ; 
 char* spin ; 
 char* spin_cp ; 

__attribute__((used)) static char
spin_char(void)
{
	char ch;

	if (*spin_cp == '\0')
		spin_cp = spin;
	ch = *spin_cp;

	/* Advance the spinner to the next char */
	if (++spin_cp >= (spin + SPIN_SIZE))
		spin_cp = spin;

	return (ch);
}