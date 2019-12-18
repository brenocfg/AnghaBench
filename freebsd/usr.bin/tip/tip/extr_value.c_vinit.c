#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int v_type; char* v_value; int v_access; int /*<<< orphan*/ * v_name; } ;
typedef  TYPE_1__ value_t ;
typedef  int /*<<< orphan*/  file ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENVIRON ; 
 size_t EXCEPTIONS ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  HOME ; 
 int IREMOTE ; 
 int PUBLIC ; 
 int WRITE ; 
 int /*<<< orphan*/ * address (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setnumber (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 char* value (int /*<<< orphan*/ ) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  vlex (char*) ; 
 TYPE_1__* vtable ; 

void
vinit(void)
{
	char file[FILENAME_MAX], *cp;
	value_t *p;
	FILE *fp;

	for (p = vtable; p->v_name != NULL; p++) {
		if (p->v_type&ENVIRON)
			if ((cp = getenv(p->v_name)))
				p->v_value = cp;
		if (p->v_type&IREMOTE)
			setnumber(p->v_value, *address(p->v_value));
	}
	/*
	 * Read the .tiprc file in the HOME directory
	 *  for sets
	 */
	cp = value(HOME);
	if (cp == NULL) {
		(void)fprintf(stderr, 
		    "$HOME not set. Skipping check for ~/.tiprc\n");
	} else if (strlen(cp) + sizeof("/.tiprc") > sizeof(file)) {
		(void)fprintf(stderr, "Home directory path too long: %s\n",
		    value(HOME));
	} else {
		snprintf(file, sizeof file, "%s/.tiprc", value(HOME));
		if ((fp = fopen(file, "r")) != NULL) {
			char *tp;

			while (fgets(file, sizeof(file)-1, fp) != NULL) {
				if (vflag)
					printf("set %s", file);
				if ((tp = strrchr(file, '\n')))
					*tp = '\0';
				vlex(file);
			}
			fclose(fp);
		}
	}
	/*
	 * To allow definition of exception prior to fork
	 */
	vtable[EXCEPTIONS].v_access &= ~(WRITE<<PUBLIC);
}