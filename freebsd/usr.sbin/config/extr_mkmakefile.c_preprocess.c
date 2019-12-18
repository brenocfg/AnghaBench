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
 int /*<<< orphan*/  sanitize_envline (char*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static bool
preprocess(char *line, char *result)
{
	char *s;

	/* Strip any comments */
	if ((s = strchr(line, '#')) != NULL)
		*s = '\0';
	sanitize_envline(result, line);
	/* Return true if it's non-empty */
	return (*result != '\0');
}