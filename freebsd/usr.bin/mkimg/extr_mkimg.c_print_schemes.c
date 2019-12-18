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
struct mkimg_scheme {char* name; char* description; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 struct mkimg_scheme* scheme_iterate (struct mkimg_scheme*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_schemes(int usage)
{
	struct mkimg_scheme *s;
	const char *sep;

	if (usage) {
		fprintf(stderr, "    schemes:\n");
		s = NULL;
		while ((s = scheme_iterate(s)) != NULL) {
			fprintf(stderr, "\t%s\t-  %s\n", s->name,
			    s->description);
		}
	} else {
		sep = "";
		s = NULL;
		while ((s = scheme_iterate(s)) != NULL) {
			printf("%s%s", sep, s->name);
			sep = " ";
		}
		putchar('\n');
	}
}