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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getdelim (char**,size_t*,char,int /*<<< orphan*/ ) ; 
 int n_opt ; 
 int o_opt ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int
handle_existing_file(char **path)
{
	size_t alen;
	ssize_t len;
	char buf[4];

	for (;;) {
		fprintf(stderr,
		    "replace %s? [y]es, [n]o, [A]ll, [N]one, [r]ename: ",
		    *path);
		if (fgets(buf, sizeof(buf), stdin) == NULL) {
			clearerr(stdin);
			printf("NULL\n(EOF or read error, "
			    "treating as \"[N]one\"...)\n");
			n_opt = 1;
			return -1;
		}
		switch (*buf) {
		case 'A':
			o_opt = 1;
			/* FALLTHROUGH */
		case 'y':
		case 'Y':
			(void)unlink(*path);
			return 1;
		case 'N':
			n_opt = 1;
			/* FALLTHROUGH */
		case 'n':
			return -1;
		case 'r':
		case 'R':
			printf("New name: ");
			fflush(stdout);
			free(*path);
			*path = NULL;
			alen = 0;
			len = getdelim(path, &alen, '\n', stdin);
			if ((*path)[len - 1] == '\n')
				(*path)[len - 1] = '\0';
			return 0;
		default:
			break;
		}
	}
}