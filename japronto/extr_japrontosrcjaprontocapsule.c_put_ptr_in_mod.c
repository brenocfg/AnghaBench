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
 int /*<<< orphan*/ * PyCapsule_New (void*,char const*,int /*<<< orphan*/ *) ; 
 int PyModule_AddObject (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

PyObject* put_ptr_in_mod(PyObject* m, void* ptr, const char* attr_name,
                         const char* capsule_name)
{
  PyObject* capsule = NULL;

  capsule = PyCapsule_New(ptr, capsule_name, NULL);
  if(!capsule)
    goto error;

  if(PyModule_AddObject(m, attr_name, capsule) == -1)
    goto error;

  Py_INCREF(capsule);
  goto finally;

  error:
  Py_XDECREF(capsule);
  capsule = NULL;

  finally:
  return capsule;
}