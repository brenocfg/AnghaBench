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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ gottoprec ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/ * toprec ; 
 scalar_t__ topreclen ; 

int
cgetset(const char *ent)
{
	if (ent == NULL) {
		if (toprec)
			free(toprec);
                toprec = NULL;
                topreclen = 0;
                return (0);
        }
        topreclen = strlen(ent);
        if ((toprec = malloc (topreclen + 1)) == NULL) {
		errno = ENOMEM;
                return (-1);
	}
	gottoprec = 0;
        (void)strcpy(toprec, ent);
        return (0);
}