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
struct au_class_ent {int /*<<< orphan*/  ac_class; int /*<<< orphan*/  ac_desc; int /*<<< orphan*/  ac_name; } ;

/* Variables and functions */
 scalar_t__ AU_CLASS_DESC_MAX ; 
 scalar_t__ AU_CLASS_NAME_MAX ; 
 int /*<<< orphan*/  classdelim ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 char* strtok_r (char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct au_class_ent *
classfromstr(char *str, struct au_class_ent *c)
{
	char *classname, *classdesc, *classflag;
	char *last;

	/* Each line contains flag:name:desc. */
	classflag = strtok_r(str, classdelim, &last);
	classname = strtok_r(NULL, classdelim, &last);
	classdesc = strtok_r(NULL, classdelim, &last);

	if ((classflag == NULL) || (classname == NULL) || (classdesc == NULL))
		return (NULL);

	/*
	 * Check for very large classnames.
	 */
	if (strlen(classname) >= AU_CLASS_NAME_MAX)
		return (NULL);
	strlcpy(c->ac_name, classname, AU_CLASS_NAME_MAX);

	/*
	 * Check for very large class description.
	 */
	if (strlen(classdesc) >= AU_CLASS_DESC_MAX)
		return (NULL);
	strlcpy(c->ac_desc, classdesc, AU_CLASS_DESC_MAX);
	c->ac_class = strtoul(classflag, (char **) NULL, 0);

	return (c);
}