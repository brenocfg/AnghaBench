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
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ PyBool_Check (int /*<<< orphan*/ *) ; 
 char* PyBytes_AsString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyDict_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyDict_Next (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyFloat_AsDouble (int /*<<< orphan*/ *) ; 
 scalar_t__ PyFloat_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyInt_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyLong_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySequence_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PySequence_Length (int /*<<< orphan*/ *) ; 
 char* PyString_AsString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyString_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUnicode_AsASCIIString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  UCL_ARRAY ; 
 int /*<<< orphan*/  UCL_OBJECT ; 
 int /*<<< orphan*/  ucl_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ucl_object_frombool (int) ; 
 int /*<<< orphan*/ * ucl_object_fromdouble (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ucl_object_fromint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ucl_object_fromstring (char*) ; 
 int /*<<< orphan*/  ucl_object_insert_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ucl_object_new () ; 
 int /*<<< orphan*/ * ucl_object_typed_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ucl_object_t *
_iterate_python (PyObject *obj)
{
	if (obj == Py_None) {
		return ucl_object_new();
	}
	else if (PyBool_Check (obj)) {
		return ucl_object_frombool (obj == Py_True);
	}
#if PY_MAJOR_VERSION < 3
	else if (PyInt_Check (obj)) {
		return ucl_object_fromint (PyInt_AsLong (obj));
	}
#endif
	else if (PyLong_Check (obj)) {
		return ucl_object_fromint (PyLong_AsLong (obj));
	}
	else if (PyFloat_Check (obj)) {
		return ucl_object_fromdouble (PyFloat_AsDouble (obj));
	}
	else if (PyUnicode_Check (obj)) {
		ucl_object_t *ucl_str;
		PyObject *str = PyUnicode_AsASCIIString(obj);
		ucl_str = ucl_object_fromstring (PyBytes_AsString (str));
		Py_DECREF(str);
		return ucl_str;
	}
#if PY_MAJOR_VERSION < 3
	else if (PyString_Check (obj)) {
		return ucl_object_fromstring (PyString_AsString (obj));
	}
#endif
	else if (PyDict_Check(obj)) {
		PyObject *key, *value;
		Py_ssize_t pos = 0;
		ucl_object_t *top, *elm;
		char *keystr = NULL;

		top = ucl_object_typed_new (UCL_OBJECT);

		while (PyDict_Next(obj, &pos, &key, &value)) {
			elm = _iterate_python(value);
			
			if (PyUnicode_Check(key)) {
				PyObject *keyascii = PyUnicode_AsASCIIString(key);
				keystr = PyBytes_AsString(keyascii);
				Py_DECREF(keyascii);
			}
#if PY_MAJOR_VERSION < 3
			else if (PyString_Check(key)) {
				keystr = PyString_AsString(key);
			}
#endif
			else {
				PyErr_SetString(PyExc_TypeError, "Unknown key type");
				return NULL;
			}

			ucl_object_insert_key (top, elm, keystr, 0, true);
		}

		return top;
	}
	else if (PySequence_Check(obj)) {
		PyObject *value;
		Py_ssize_t len, pos;
		ucl_object_t *top, *elm;

		len  = PySequence_Length(obj);
		top = ucl_object_typed_new (UCL_ARRAY);

		for (pos = 0; pos < len; pos++) {
			value = PySequence_GetItem(obj, pos);
			elm = _iterate_python(value);
			ucl_array_append(top, elm);
		}

		return top;
	}
	else {
		PyErr_SetString(PyExc_TypeError, "Unhandled object type");
		return NULL;
	}

	return NULL;
}