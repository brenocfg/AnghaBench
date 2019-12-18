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
typedef  scalar_t__ ucl_emitter_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 scalar_t__ UCL_EMIT_CONFIG ; 
 scalar_t__ UCL_EMIT_MAX ; 
 int /*<<< orphan*/ * _iterate_python (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ucl_object_emit (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
ucl_dump (PyObject *self, PyObject *args)
{
	PyObject *obj;
	ucl_emitter_t emitter;
	ucl_object_t *root = NULL;

	emitter = UCL_EMIT_CONFIG;

	if (!PyArg_ParseTuple(args, "O|i", &obj, &emitter)) {
		PyErr_SetString(PyExc_TypeError, "Unhandled object type");
		return NULL;
	}

	if (emitter >= UCL_EMIT_MAX) {
		PyErr_SetString(PyExc_TypeError, "Invalid emitter type");
		return NULL;
	}

	if (obj == Py_None) {
		Py_RETURN_NONE;
	}

	root = _iterate_python(obj);
	if (root) {
		PyObject *ret;
		char *buf;

		buf = (char *) ucl_object_emit (root, emitter);
		ucl_object_unref (root);
#if PY_MAJOR_VERSION < 3
		ret = PyString_FromString (buf);
#else
		ret = PyUnicode_FromString (buf);
#endif
		free(buf);

		return ret;
	}

	return NULL;
}