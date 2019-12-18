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
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct ucl_parser {int dummy; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int perform_tests (int /*<<< orphan*/  const*) ; 
 int read_stdin (char**) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * ucl_object_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_parser_add_string (struct ucl_parser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_parser_free (struct ucl_parser*) ; 
 char* ucl_parser_get_error (struct ucl_parser*) ; 
 int /*<<< orphan*/ * ucl_parser_get_object (struct ucl_parser*) ; 
 struct ucl_parser* ucl_parser_new (int /*<<< orphan*/ ) ; 

int
main (int argc, char **argv)
{
	char *buf = NULL;
	struct ucl_parser *parser;
	ucl_object_t *obj = NULL;
	const ucl_object_t *elt;
	ucl_object_iter_t iter = NULL;
	int ret = 0;

	if (read_stdin (&buf) == -1) {
		exit (EXIT_FAILURE);
	}

	parser = ucl_parser_new (0);

	ucl_parser_add_string (parser, buf, 0);

	if (ucl_parser_get_error (parser) != NULL) {
		fprintf (stdout, "Error occurred: %s\n", ucl_parser_get_error (parser));
		ret = 1;
		return EXIT_FAILURE;
	}
	obj = ucl_parser_get_object (parser);
	ucl_parser_free (parser);

	while ((elt = ucl_object_iterate (obj, &iter, true)) != NULL) {
		ret = perform_tests (elt);
		if (ret != 0) {
			break;
		}
	}

	ucl_object_unref (obj);

	return ret;
}