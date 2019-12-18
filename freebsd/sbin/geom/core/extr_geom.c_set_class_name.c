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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* class_name ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 char* gclass_name ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 char tolower (char) ; 
 int /*<<< orphan*/  toupper (char) ; 

__attribute__((used)) static void
set_class_name(void)
{
	char *s1, *s2;

	s1 = class_name;
	for (; *s1 != '\0'; s1++)
		*s1 = tolower(*s1);
	gclass_name = malloc(strlen(class_name) + 1);
	if (gclass_name == NULL)
		errx(EXIT_FAILURE, "No memory");
	s1 = gclass_name;
	s2 = class_name;
	for (; *s2 != '\0'; s2++)
		*s1++ = toupper(*s2);
	*s1 = '\0';
}