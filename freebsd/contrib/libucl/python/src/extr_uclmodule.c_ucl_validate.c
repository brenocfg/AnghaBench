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
struct ucl_schema_error {char* msg; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  Py_RETURN_TRUE ; 
 int /*<<< orphan*/  SchemaError ; 
 int /*<<< orphan*/ * _iterate_python (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/ *) ; 
 int ucl_object_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ucl_schema_error*) ; 

__attribute__((used)) static PyObject *
ucl_validate (PyObject *self, PyObject *args)
{
	PyObject *dataobj, *schemaobj;
	ucl_object_t *data, *schema;
	bool r;
	struct ucl_schema_error err;

	if (!PyArg_ParseTuple (args, "OO", &schemaobj, &dataobj)) {
		PyErr_SetString (PyExc_TypeError, "Unhandled object type");
		return NULL;
	}

	schema = _iterate_python(schemaobj);
	if (!schema)
		return NULL;

	data = _iterate_python(dataobj);
	if (!data)
		return NULL;

	// validation
	r = ucl_object_validate (schema, data, &err);
	ucl_object_unref (schema);
	ucl_object_unref (data);

	if (!r) {
		PyErr_SetString (SchemaError, err.msg);
		return NULL;
	}

	Py_RETURN_TRUE;
}