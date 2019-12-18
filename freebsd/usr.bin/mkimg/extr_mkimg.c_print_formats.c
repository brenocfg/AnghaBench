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
struct mkimg_format {char* name; char* description; } ;

/* Variables and functions */
 struct mkimg_format* format_iterate (struct mkimg_format*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_formats(int usage)
{
	struct mkimg_format *f;
	const char *sep;

	if (usage) {
		fprintf(stderr, "    formats:\n");
		f = NULL;
		while ((f = format_iterate(f)) != NULL) {
			fprintf(stderr, "\t%s\t-  %s\n", f->name,
			    f->description);
		}
	} else {
		sep = "";
		f = NULL;
		while ((f = format_iterate(f)) != NULL) {
			printf("%s%s", sep, f->name);
			sep = " ";
		}
		putchar('\n');
	}
}