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
 int /*<<< orphan*/  XXX ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

char   *
usb_strdup(const char *str)
{
	char *tmp;
	int len;

	len = 1 + strlen(str);

	tmp = malloc(len,XXX,XXX);
	if (tmp == NULL)
		return (NULL);

	memcpy(tmp, str, len);
	return (tmp);
}