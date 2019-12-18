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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NewException (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyModule_AddIntMacro (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyModule_AddObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SchemaError ; 
 int /*<<< orphan*/  UCL_EMIT_CONFIG ; 
 int /*<<< orphan*/  UCL_EMIT_JSON ; 
 int /*<<< orphan*/  UCL_EMIT_JSON_COMPACT ; 
 int /*<<< orphan*/  UCL_EMIT_MSGPACK ; 
 int /*<<< orphan*/  UCL_EMIT_YAML ; 

__attribute__((used)) static void
init_macros(PyObject *mod)
{
	PyModule_AddIntMacro(mod, UCL_EMIT_JSON);
	PyModule_AddIntMacro(mod, UCL_EMIT_JSON_COMPACT);
	PyModule_AddIntMacro(mod, UCL_EMIT_CONFIG);
	PyModule_AddIntMacro(mod, UCL_EMIT_YAML);
	PyModule_AddIntMacro(mod, UCL_EMIT_MSGPACK);

	SchemaError = PyErr_NewException("ucl.SchemaError", NULL, NULL);
	Py_INCREF(SchemaError);
	PyModule_AddObject(mod, "SchemaError", SchemaError);
}