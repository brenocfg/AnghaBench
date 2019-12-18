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
typedef  int /*<<< orphan*/  const ucl_object_t ;
struct ucl_parser {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 unsigned char* realloc (unsigned char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  ucl_obj_dump (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* ucl_object_lookup (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ucl_parser_add_chunk (struct ucl_parser*,unsigned char*,int) ; 
 int /*<<< orphan*/  ucl_parser_free (struct ucl_parser*) ; 
 char* ucl_parser_get_error (struct ucl_parser*) ; 
 int /*<<< orphan*/  const* ucl_parser_get_object (struct ucl_parser*) ; 
 struct ucl_parser* ucl_parser_new (int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	const char *fn = NULL;
	unsigned char *inbuf;
	struct ucl_parser *parser;
	int k, ret = 0, r = 0;
	ssize_t bufsize;
	ucl_object_t *obj = NULL;
	const ucl_object_t *par;
	FILE *in;

	if (argc > 1) {
		fn = argv[1];
	}

	if (fn != NULL) {
		in = fopen (fn, "r");
		if (in == NULL) {
			exit (-errno);
		}
	}
	else {
		in = stdin;
	}

	parser = ucl_parser_new (0);
	inbuf = malloc (BUFSIZ);
	bufsize = BUFSIZ;
	r = 0;

	while (!feof (in) && !ferror (in)) {
		if (r == bufsize) {
			inbuf = realloc (inbuf, bufsize * 2);
			bufsize *= 2;
			if (inbuf == NULL) {
				perror ("realloc");
				exit (EXIT_FAILURE);
			}
		}
		r += fread (inbuf + r, 1, bufsize - r, in);
	}

	if (ferror (in)) {
		fprintf (stderr, "Failed to read the input file.\n");
		exit (EXIT_FAILURE);
	}

	ucl_parser_add_chunk (parser, inbuf, r);
	fclose (in);
	if (ucl_parser_get_error(parser)) {
		printf ("Error occured: %s\n", ucl_parser_get_error(parser));
		ret = 1;
		goto end;
	}

	obj = ucl_parser_get_object (parser);
	if (ucl_parser_get_error (parser)) {
		printf ("Error occured: %s\n", ucl_parser_get_error(parser));
		ret = 1;
		goto end;
	}

	if (argc > 2) {
		for (k = 2; k < argc; k++) {
			printf ("search for \"%s\"... ", argv[k]);
			par = ucl_object_lookup (obj, argv[k]);
			printf ("%sfound\n", (par == NULL )?"not ":"");
			ucl_obj_dump (par, 0);
		}
	}
	else {
		ucl_obj_dump (obj, 0);
	}

end:
	if (parser != NULL) {
		ucl_parser_free (parser);
	}
	if (obj != NULL) {
		ucl_object_unref (obj);
	}

	return ret;
}