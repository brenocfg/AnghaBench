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
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* strdup (char const*) ; 

char *
ftp_strdup(const char *str)
{
	char *s;

	if (str == NULL)
		errx(1, "ftp_strdup: called with NULL argument");
	s = strdup(str);
	if (s == NULL)
		err(1, "Unable to allocate memory for string copy");
	return (s);
}