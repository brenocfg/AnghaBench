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
struct stat {int dummy; } ;
struct html {char* base_man1; char* base_man2; char* base_includes; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  print_byte (struct html*,char) ; 
 int /*<<< orphan*/  print_encode (struct html*,char const*,char const*,int) ; 
 int stat (char*,struct stat*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void
print_href(struct html *h, const char *name, const char *sec, int man)
{
	struct stat	 sb;
	const char	*p, *pp;
	char		*filename;

	if (man) {
		pp = h->base_man1;
		if (h->base_man2 != NULL) {
			mandoc_asprintf(&filename, "%s.%s", name, sec);
			if (stat(filename, &sb) == -1)
				pp = h->base_man2;
			free(filename);
		}
	} else
		pp = h->base_includes;

	while ((p = strchr(pp, '%')) != NULL) {
		print_encode(h, pp, p, 1);
		if (man && p[1] == 'S') {
			if (sec == NULL)
				print_byte(h, '1');
			else
				print_encode(h, sec, NULL, 1);
		} else if ((man && p[1] == 'N') ||
		    (man == 0 && p[1] == 'I'))
			print_encode(h, name, NULL, 1);
		else
			print_encode(h, p, p + 2, 1);
		pp = p + 2;
	}
	if (*pp != '\0')
		print_encode(h, pp, NULL, 1);
}