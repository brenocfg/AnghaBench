#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ud; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ value; int /*<<< orphan*/ * key; } ;
typedef  TYPE_2__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyBytes_FromString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_SystemError ; 
 int /*<<< orphan*/  PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyList_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ UCL_ARRAY ; 
 scalar_t__ UCL_OBJECT ; 
 scalar_t__ UCL_USERDATA ; 
 int /*<<< orphan*/ * _basic_ucl_type (TYPE_2__ const*) ; 
 TYPE_2__* ucl_object_iterate (TYPE_2__ const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ucl_object_key (TYPE_2__ const*) ; 

__attribute__((used)) static PyObject *
_iterate_valid_ucl (ucl_object_t const *obj)
{
	const ucl_object_t *tmp;
	ucl_object_iter_t it = NULL;

	tmp = obj;

	while ((obj = ucl_object_iterate (tmp, &it, false))) {
		PyObject *val;

		val = _basic_ucl_type(obj);
		if (!val) {
			PyObject *key = NULL;

			if (obj->key != NULL) {
				key = Py_BuildValue("s", ucl_object_key(obj));
			}

			if (obj->type == UCL_OBJECT) {
				const ucl_object_t *cur;
				ucl_object_iter_t it_obj = NULL;

				val = PyDict_New();

				while ((cur = ucl_object_iterate (obj, &it_obj, true))) {
					PyObject *keyobj = Py_BuildValue("s",ucl_object_key(cur));
					PyDict_SetItem(val, keyobj, _iterate_valid_ucl(cur));
				}
			} else if (obj->type == UCL_ARRAY) {
				const ucl_object_t *cur;
				ucl_object_iter_t it_obj = NULL;

				val = PyList_New(0);

				while ((cur = ucl_object_iterate (obj, &it_obj, true))) {
					PyList_Append(val, _iterate_valid_ucl(cur));
				}
			} else if (obj->type == UCL_USERDATA) {
				// XXX: this should be
				// PyBytes_FromStringAndSize; where is the
				// length from?
				val = PyBytes_FromString(obj->value.ud);
			}
		}
		return val;
	}

	PyErr_SetString(PyExc_SystemError, "unhandled type");
	return NULL;
}