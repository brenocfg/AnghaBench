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
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mkpath (char*) ; 
 int /*<<< orphan*/  pfatal (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strrchr (char*,char) ; 

void
makedirs(const char *filename, bool striplast)
{
	char	*tmpbuf;

	if ((tmpbuf = strdup(filename)) == NULL)
		fatal("out of memory\n");

	if (striplast) {
		char	*s = strrchr(tmpbuf, '/');
		if (s == NULL) {
			free(tmpbuf);
			return;	/* nothing to be done */
		}
		*s = '\0';
	}
	if (mkpath(tmpbuf) != 0)
		pfatal("creation of %s failed", tmpbuf);
	free(tmpbuf);
}