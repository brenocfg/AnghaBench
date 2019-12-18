#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int type; } ;
typedef  TYPE_1__ ucl_object_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyBool_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,long long) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
#define  UCL_BOOLEAN 133 
#define  UCL_FLOAT 132 
#define  UCL_INT 131 
#define  UCL_NULL 130 
#define  UCL_STRING 129 
#define  UCL_TIME 128 
 int /*<<< orphan*/  ucl_object_toboolean (TYPE_1__ const*) ; 
 long long ucl_object_todouble (TYPE_1__ const*) ; 
 scalar_t__ ucl_object_toint (TYPE_1__ const*) ; 
 long long ucl_object_tostring (TYPE_1__ const*) ; 

__attribute__((used)) static PyObject *
_basic_ucl_type (ucl_object_t const *obj)
{
	switch (obj->type) {
	case UCL_INT:
		return Py_BuildValue ("L", (long long)ucl_object_toint (obj));
	case UCL_FLOAT:
		return Py_BuildValue ("d", ucl_object_todouble (obj));
	case UCL_STRING:
		return Py_BuildValue ("s", ucl_object_tostring (obj));
	case UCL_BOOLEAN:
		return PyBool_FromLong (ucl_object_toboolean (obj));
	case UCL_TIME:
		return Py_BuildValue ("d", ucl_object_todouble (obj));
	case UCL_NULL:
		Py_RETURN_NONE;
	}
	return NULL;
}