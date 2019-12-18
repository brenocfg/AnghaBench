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
struct au_class_ent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CLASS_FILE ; 
 int /*<<< orphan*/  AU_LINE_MAX ; 
 int /*<<< orphan*/ * classfromstr (char*,struct au_class_ent*) ; 
 int /*<<< orphan*/ * fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fp ; 
 char* linestr ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static struct au_class_ent *
getauclassent_r_locked(struct au_class_ent *c)
{
	char *tokptr, *nl;

	if ((fp == NULL) && ((fp = fopen(AUDIT_CLASS_FILE, "r")) == NULL))
		return (NULL);

	/*
	 * Read until next non-comment line is found, or EOF.
	 */
	while (1) {
		if (fgets(linestr, AU_LINE_MAX, fp) == NULL)
			return (NULL);

		/* Skip comments. */
		if (linestr[0] == '#')
			continue;

		/* Remove trailing new line character. */
		if ((nl = strrchr(linestr, '\n')) != NULL)
			*nl = '\0';

		/* Parse tokptr to au_class_ent components. */
		tokptr = linestr;
		if (classfromstr(tokptr, c) == NULL)
			return (NULL);
		break;
	}

	return (c);
}