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
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 scalar_t__ tolower (unsigned char) ; 

__attribute__((used)) static int
aindex(char const * arr[], char const ** str, int len)
{
	int             l, i;
	char            mystr[32];

	mystr[len] = '\0';
	l = strlen(strncpy(mystr, *str, len));
	for (i = 0; i < l; i++)
		mystr[i] = (char) tolower((unsigned char)mystr[i]);
	for (i = 0; arr[i] && strcmp(mystr, arr[i]) != 0; i++);
	if (arr[i] == NULL)
		i = -1;
	else {			/* Skip past it */
		while (**str && isalpha((unsigned char)**str))
			++(*str);
		/* And any following whitespace */
		while (**str && (**str == ',' || isspace((unsigned char)**str)))
			++(*str);
	}			/* Return index */
	return i;
}