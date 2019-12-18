#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_4__ {void* prefixval; void* prefixname; } ;
struct TYPE_3__ {void* uval; void* uname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_READ ; 
 size_t MAXPREFIXES ; 
 size_t MAXUNITS ; 
 int /*<<< orphan*/  SEPARATOR ; 
 char* UNITSFILE ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_rights_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* dupstr (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* getenv (char*) ; 
 size_t prefixcount ; 
 TYPE_2__* prefixtable ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (void*,char*) ; 
 int strcspn (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 
 size_t unitcount ; 
 TYPE_1__* unittable ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void 
readunits(const char *userfile)
{
	FILE *unitfile;
	char line[512], *lineptr;
	int len, linenum, i;
	cap_rights_t unitfilerights;

	unitcount = 0;
	linenum = 0;

	if (userfile) {
		unitfile = fopen(userfile, "r");
		if (!unitfile)
			errx(1, "unable to open units file '%s'", userfile);
	}
	else {
		unitfile = fopen(UNITSFILE, "r");
		if (!unitfile) {
			char *direc, *env;
			char filename[1000];

			env = getenv("PATH");
			if (env) {
				direc = strtok(env, SEPARATOR);
				while (direc) {
					snprintf(filename, sizeof(filename),
					    "%s/%s", direc, UNITSFILE);
					unitfile = fopen(filename, "rt");
					if (unitfile)
						break;
					direc = strtok(NULL, SEPARATOR);
				}
			}
			if (!unitfile)
				errx(1, "can't find units file '%s'", UNITSFILE);
		}
	}
	cap_rights_init(&unitfilerights, CAP_READ, CAP_FSTAT);
	if (caph_rights_limit(fileno(unitfile), &unitfilerights) < 0)
		err(1, "cap_rights_limit() failed");
	while (!feof(unitfile)) {
		if (!fgets(line, sizeof(line), unitfile))
			break;
		linenum++;
		lineptr = line;
		if (*lineptr == '/' || *lineptr == '#')
			continue;
		lineptr += strspn(lineptr, " \n\t");
		len = strcspn(lineptr, " \n\t");
		lineptr[len] = 0;
		if (!strlen(lineptr))
			continue;
		if (lineptr[strlen(lineptr) - 1] == '-') { /* it's a prefix */
			if (prefixcount == MAXPREFIXES) {
				warnx("memory for prefixes exceeded in line %d", linenum);
				continue;
			}
			lineptr[strlen(lineptr) - 1] = 0;
			prefixtable[prefixcount].prefixname = dupstr(lineptr);
			for (i = 0; i < prefixcount; i++)
				if (!strcmp(prefixtable[i].prefixname, lineptr)) {
					warnx("redefinition of prefix '%s' on line %d ignored",
					    lineptr, linenum);
					continue;
				}
			lineptr += len + 1;
			lineptr += strspn(lineptr, " \n\t");
			len = strcspn(lineptr, "\n\t");
			if (len == 0) {
				warnx("unexpected end of prefix on line %d",
				    linenum);
				continue;
			}
			lineptr[len] = 0;
			prefixtable[prefixcount++].prefixval = dupstr(lineptr);
		}
		else {		/* it's not a prefix */
			if (unitcount == MAXUNITS) {
				warnx("memory for units exceeded in line %d", linenum);
				continue;
			}
			unittable[unitcount].uname = dupstr(lineptr);
			for (i = 0; i < unitcount; i++)
				if (!strcmp(unittable[i].uname, lineptr)) {
					warnx("redefinition of unit '%s' on line %d ignored",
					    lineptr, linenum);
					continue;
				}
			lineptr += len + 1;
			lineptr += strspn(lineptr, " \n\t");
			if (!strlen(lineptr)) {
				warnx("unexpected end of unit on line %d",
				    linenum);
				continue;
			}
			len = strcspn(lineptr, "\n\t");
			lineptr[len] = 0;
			unittable[unitcount++].uval = dupstr(lineptr);
		}
	}
	fclose(unitfile);
}