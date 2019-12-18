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
struct re_entry {int re_negate; int /*<<< orphan*/  re_regexp; void* re_pattern; } ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct re_entry*,int /*<<< orphan*/ ) ; 
 struct re_entry* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  re_glue ; 
 int /*<<< orphan*/  re_head ; 
 int regcomp (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 void* strdup (char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
parse_regexp(char *re_string)
{
	char *orig, *copy, re_error[64];
	struct re_entry *rep;
	int error, nstrs, i, len;

	copy = strdup(re_string);
	orig = copy;
	len = strlen(copy);
	for (nstrs = 0, i = 0; i < len; i++) {
		if (copy[i] == ',' && i > 0) {
			if (copy[i - 1] == '\\')
				strlcpy(&copy[i - 1], &copy[i], len);
			else {
				nstrs++;
				copy[i] = '\0';
			}
		}
	}
	TAILQ_INIT(&re_head);
	for (i = 0; i < nstrs + 1; i++) {
		rep = calloc(1, sizeof(*rep));
		if (rep == NULL) {
			(void) fprintf(stderr, "calloc: %s\n",
			    strerror(errno));
			exit(1);
		}
		if (*copy == '~') {
			copy++;
			rep->re_negate = 1;
		}
		rep->re_pattern = strdup(copy);
		error = regcomp(&rep->re_regexp, rep->re_pattern,
		    REG_EXTENDED | REG_NOSUB);
		if (error != 0) {
			regerror(error, &rep->re_regexp, re_error, 64);
			(void) fprintf(stderr, "regcomp: %s\n", re_error);
			exit(1);
		}
		TAILQ_INSERT_TAIL(&re_head, rep, re_glue);
		len = strlen(copy);
		copy += len + 1;
	}
	free(orig);
}