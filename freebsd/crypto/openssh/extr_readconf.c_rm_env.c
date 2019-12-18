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
struct TYPE_3__ {int num_send_env; char** send_env; } ;
typedef  TYPE_1__ Options ;

/* Variables and functions */
 int /*<<< orphan*/  debug3 (char*,char const*,int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  match_pattern (char*,char const*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
rm_env(Options *options, const char *arg, const char *filename, int linenum)
{
	int i, j;
	char *cp;

	/* Remove an environment variable */
	for (i = 0; i < options->num_send_env; ) {
		cp = xstrdup(options->send_env[i]);
		if (!match_pattern(cp, arg + 1)) {
			free(cp);
			i++;
			continue;
		}
		debug3("%s line %d: removing environment %s",
		    filename, linenum, cp);
		free(cp);
		free(options->send_env[i]);
		options->send_env[i] = NULL;
		for (j = i; j < options->num_send_env - 1; j++) {
			options->send_env[j] = options->send_env[j + 1];
			options->send_env[j + 1] = NULL;
		}
		options->num_send_env--;
		/* NB. don't increment i */
	}
}