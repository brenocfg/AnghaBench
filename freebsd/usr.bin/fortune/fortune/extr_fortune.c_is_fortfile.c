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
 int /*<<< orphan*/  All_forts ; 
 int /*<<< orphan*/  DPRINTF (int,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 scalar_t__ Fortunes_only ; 
 int Offend ; 
 int /*<<< orphan*/  R_OK ; 
 int TRUE ; 
 scalar_t__ WriteToDisk ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char* copy (char const*,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int
is_fortfile(const char *file, char **datp, char **posp, int check_for_offend)
{
	int	i;
	const char	*sp;
	char	*datfile;
	static const char *suflist[] = {
		/* list of "illegal" suffixes" */
		"dat", "pos", "c", "h", "p", "i", "f",
		"pas", "ftn", "ins.c", "ins,pas",
		"ins.ftn", "sml",
		NULL
	};

	DPRINTF(2, (stderr, "is_fortfile(%s) returns ", file));

	/*
	 * Preclude any -o files for offendable people, and any non -o
	 * files for completely offensive people.
	 */
	if (check_for_offend && !All_forts) {
		i = strlen(file);
		if (Offend ^ (file[i - 2] == '-' && file[i - 1] == 'o')) {
			DPRINTF(2, (stderr, "FALSE (offending file)\n"));
			return (FALSE);
		}
	}

	if ((sp = strrchr(file, '/')) == NULL)
		sp = file;
	else
		sp++;
	if (*sp == '.') {
		DPRINTF(2, (stderr, "FALSE (file starts with '.')\n"));
		return (FALSE);
	}
	if (Fortunes_only && strncmp(sp, "fortunes", 8) != 0) {
		DPRINTF(2, (stderr, "FALSE (check fortunes only)\n"));
		return (FALSE);
	}
	if ((sp = strrchr(sp, '.')) != NULL) {
		sp++;
		for (i = 0; suflist[i] != NULL; i++)
			if (strcmp(sp, suflist[i]) == 0) {
				DPRINTF(2, (stderr, "FALSE (file has suffix \".%s\")\n", sp));
				return (FALSE);
			}
	}

	datfile = copy(file, (unsigned int) (strlen(file) + 4)); /* +4 for ".dat" */
	strcat(datfile, ".dat");
	if (access(datfile, R_OK) < 0) {
		DPRINTF(2, (stderr, "FALSE (no readable \".dat\" file)\n"));
		free(datfile);
		return (FALSE);
	}
	if (datp != NULL)
		*datp = datfile;
	else
		free(datfile);
	if (posp != NULL) {
		if (WriteToDisk) {
			*posp = copy(file, (unsigned int) (strlen(file) + 4)); /* +4 for ".dat" */
			strcat(*posp, ".pos");
		}
		else {
			*posp = NULL;
		}
	}
	DPRINTF(2, (stderr, "TRUE\n"));

	return (TRUE);
}