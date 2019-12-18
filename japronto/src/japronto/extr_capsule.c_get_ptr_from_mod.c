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
 void* PyCapsule_GetPointer (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * PyImport_ImportModule (char const*) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

void* get_ptr_from_mod(const char* module_name, const char* attr_name,
                       const char* capsule_name)
{
  void* ptr;
  PyObject* module = NULL;
  PyObject* capsule = NULL;

  module = PyImport_ImportModule(module_name);
  if(!module)
    goto error;

  capsule = PyObject_GetAttrString(module, attr_name);
  if(!capsule)
    goto error;

  ptr = PyCapsule_GetPointer(capsule, capsule_name);
  if(!ptr)
    goto error;

  goto finally;

  error:
  ptr = NULL;

  finally:
  Py_XDECREF(capsule);
  Py_XDECREF(module);
  return ptr;
}