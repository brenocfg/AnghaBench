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
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *
efi_make_tail(char *suffix)
{
	char *tail;

	tail = NULL;
	if (suffix != NULL)
		(void)asprintf(&tail, "/%s", suffix);
	else
		tail = strdup("");
	return (tail);
}