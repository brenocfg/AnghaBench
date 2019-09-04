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
typedef  int /*<<< orphan*/ * PyMODINIT_FUNC ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CHECK_INTERVAL ; 
 int /*<<< orphan*/ * PyLong_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyModule_AddObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyModule_Create (int /*<<< orphan*/ *) ; 
 scalar_t__ PyType_Ready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReaperType ; 
 int /*<<< orphan*/  creaper ; 
 int /*<<< orphan*/ * default_check_interval ; 
 int /*<<< orphan*/  import_capi (char*) ; 
 int /*<<< orphan*/  protocol_capi ; 

PyMODINIT_FUNC
PyInit_creaper(void)
{
  PyObject* m = NULL;
  default_check_interval = NULL;

  if (PyType_Ready(&ReaperType) < 0)
    goto error;

  m = PyModule_Create(&creaper);
  if(!m)
    goto error;

  Py_INCREF(&ReaperType);
  PyModule_AddObject(m, "Reaper", (PyObject*)&ReaperType);

  if(!(default_check_interval = PyLong_FromLong(DEFAULT_CHECK_INTERVAL)))
    goto error;

  protocol_capi = import_capi("japronto.protocol.cprotocol");
  if(!protocol_capi)
    goto error;

  goto finally;

  error:
  Py_XDECREF(default_check_interval);
  m = NULL;

  finally:
  return m;
}