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
struct file_name {int /*<<< orphan*/  exists; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  fetchname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  strippath ; 

__attribute__((used)) static void
p4_fetchname(struct file_name *name, char *str)
{
	char *t, *h;

	/* Skip leading whitespace. */
	while (isspace((unsigned char)*str))
		str++;

	/* Remove the file revision number. */
	for (t = str, h = NULL; *t != '\0' && !isspace((unsigned char)*t); t++)
		if (*t == '#')
			h = t;
	if (h != NULL)
		*h = '\0';

	name->path = fetchname(str, &name->exists, strippath);
}