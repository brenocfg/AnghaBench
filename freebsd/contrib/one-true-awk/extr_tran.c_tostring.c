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
 int /*<<< orphan*/  FATAL (char*,char const*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

char *tostring(const char *s)	/* make a copy of string s */
{
	char *p;

	p = (char *) malloc(strlen(s)+1);
	if (p == NULL)
		FATAL("out of space in tostring on %s", s);
	strcpy(p, s);
	return(p);
}