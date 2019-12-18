#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ziplen; int /*<<< orphan*/  normal; int /*<<< orphan*/  zipped; } ;
typedef  TYPE_1__ suffixes_t ;

/* Variables and functions */
 int NUM_SUFFIXES ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 TYPE_1__ const* suffixes ; 

__attribute__((used)) static const suffixes_t *
check_suffix(char *file, int xlate)
{
	const suffixes_t *s;
	int len = strlen(file);
	char *sp;

	for (s = suffixes; s != suffixes + NUM_SUFFIXES; s++) {
		/* if it doesn't fit in "a.suf", don't bother */
		if (s->ziplen >= len)
			continue;
		sp = file + len - s->ziplen;
		if (strcmp(s->zipped, sp) != 0)
			continue;
		if (xlate)
			strcpy(sp, s->normal);
		return s;
	}
	return NULL;
}