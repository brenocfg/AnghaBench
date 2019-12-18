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
 int /*<<< orphan*/  free (char*) ; 
 char* xstrdup (char const*) ; 
 char* xstrfmt (char*,char const*,char const*) ; 

__attribute__((used)) static void expand_base_dir(char **out, const char *in,
			    const char *base_dir, const char *def_in)
{
	free(*out);
	if (in)
		*out = xstrdup(in);
	else
		*out = xstrfmt("%s/%s", base_dir, def_in);
}