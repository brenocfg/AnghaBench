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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strlcat (char*,char* const,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char* const,size_t) ; 
 scalar_t__ strlen (char* const) ; 

char *
copy_argv(char * const *argv)
{
	size_t len = 0, n;
	char *buf;

	if (argv == NULL)
		return (NULL);

	for (n = 0; argv[n]; n++)
		len += strlen(argv[n])+1;
	if (len == 0)
		return (NULL);

	buf = malloc(len);
	if (buf == NULL)
		return (NULL);

	strlcpy(buf, argv[0], len);
	for (n = 1; argv[n]; n++) {
		strlcat(buf, " ", len);
		strlcat(buf, argv[n], len);
	}
	return (buf);
}