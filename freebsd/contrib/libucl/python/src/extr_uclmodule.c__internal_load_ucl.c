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
struct ucl_parser {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  UCL_PARSER_NO_TIME ; 
 int /*<<< orphan*/ * _iterate_valid_ucl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/ *) ; 
 int ucl_parser_add_string (struct ucl_parser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_parser_free (struct ucl_parser*) ; 
 scalar_t__ ucl_parser_get_error (struct ucl_parser*) ; 
 int /*<<< orphan*/ * ucl_parser_get_object (struct ucl_parser*) ; 
 struct ucl_parser* ucl_parser_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
_internal_load_ucl (char *uclstr)
{
	PyObject *ret;
	struct ucl_parser *parser = ucl_parser_new (UCL_PARSER_NO_TIME);
	bool r = ucl_parser_add_string(parser, uclstr, 0);

	if (r) {
		if (ucl_parser_get_error (parser)) {
			PyErr_SetString(PyExc_ValueError, ucl_parser_get_error(parser));
			ucl_parser_free(parser);
			ret = NULL;
			goto return_with_parser;
		} else {
			ucl_object_t *uclobj = ucl_parser_get_object(parser);
			ret = _iterate_valid_ucl(uclobj);
			ucl_object_unref(uclobj);
			goto return_with_parser;
		}
	}
	else {
		PyErr_SetString(PyExc_ValueError, ucl_parser_get_error (parser));
		ret = NULL;
		goto return_with_parser;
	}

return_with_parser:
	ucl_parser_free(parser);
	return ret;
}