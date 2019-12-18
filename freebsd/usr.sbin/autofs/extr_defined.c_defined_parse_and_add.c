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
 int /*<<< orphan*/  defined_add (char*,char*) ; 
 int /*<<< orphan*/  log_errx (int,char*) ; 
 char* strsep (char**,char*) ; 

void
defined_parse_and_add(char *def)
{
	char *name, *value;

	value = def;
	name = strsep(&value, "=");

	if (value == NULL || value[0] == '\0')
		log_errx(1, "missing variable value");
	if (name == NULL || name[0] == '\0')
		log_errx(1, "missing variable name");

	defined_add(name, value);
}