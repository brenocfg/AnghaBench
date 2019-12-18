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
struct flag {char* f_str; long long f_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static long long
str2flags(struct flag *tflags, char *sflags)
{
	long long flags = 0;
	unsigned int i;
	char *f;

	/* 'none' or '0' means no flags */
	if (strcmp(sflags, "none") == 0 || strcmp(sflags, "0") == 0)
		return (0);
	for (f = strtok(sflags, ",|"); f != NULL; f = strtok(NULL, ",|")) {
		for (i = 0; tflags[i].f_str != NULL; i++) {
			if (strcmp(tflags[i].f_str, f) == 0)
				break;
		}
		if (tflags[i].f_str == NULL) {
			fprintf(stderr, "unknown flag '%s'\n", f);
			exit(1);
		}
		flags |= tflags[i].f_flag;
	}
	return (flags);
}