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
 char* calloc (int,int) ; 
 scalar_t__ isascii (unsigned char) ; 
 int /*<<< orphan*/  isu8cont (char) ; 

char *
utoa(char *u)
{
	int	 len, i, j;
	char	*str;

	/* calculate the length to allocate */
	for (len = 0, i = 0; u[i] != '\0'; i++)
		if (!isu8cont(u[i]))
			len++;

	if ((str = calloc(len + 1, sizeof(char))) == NULL)
		return NULL;

	/* copy the ASCII characters to the newly allocated string */
	for (i = 0, j = 0; u[i] != '\0'; i++)
		if (!isu8cont(u[i]))
			str[j++] = isascii((unsigned char)u[i]) ? u[i] : '?';

	return str;
}