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
typedef  size_t ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 char** object_type_strings ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 

int type_from_string_gently(const char *str, ssize_t len, int gentle)
{
	int i;

	if (len < 0)
		len = strlen(str);

	for (i = 1; i < ARRAY_SIZE(object_type_strings); i++)
		if (!strncmp(str, object_type_strings[i], len) &&
		    object_type_strings[i][len] == '\0')
			return i;

	if (gentle)
		return -1;

	die(_("invalid object type \"%s\""), str);
}