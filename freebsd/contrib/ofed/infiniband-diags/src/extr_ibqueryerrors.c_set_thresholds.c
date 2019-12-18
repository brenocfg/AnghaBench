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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  set_thres (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threshold_str ; 

__attribute__((used)) static void set_thresholds(char *threshold_file)
{
	char buf[1024];
	int val = 0;
	FILE *thresf = fopen(threshold_file, "r");
	char *p_prefix, *p_last;
	char *name;
	char *val_str;
	char str[64];

	if (!thresf)
		return;

	snprintf(str, 63, "Thresholds: ");
	threshold_str = malloc(strlen(str)+1);
	if (!threshold_str) {
		fprintf(stderr, "Failed to allocate memory: %s\n",
			strerror(errno));
		exit(1);
	}
	strcpy(threshold_str, str);
	while (fgets(buf, sizeof buf, thresf) != NULL) {
		p_prefix = strtok_r(buf, "\n", &p_last);
		if (!p_prefix)
			continue; /* ignore blank lines */

		if (*p_prefix == '#')
			continue; /* ignore comment lines */

		name = strtok_r(p_prefix, "=", &p_last);
		val_str = strtok_r(NULL, "\n", &p_last);

		val = strtoul(val_str, NULL, 0);
		set_thres(name, val);
	}

	fclose(thresf);
}