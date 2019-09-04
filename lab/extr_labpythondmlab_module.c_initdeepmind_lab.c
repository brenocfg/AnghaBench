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
typedef  int /*<<< orphan*/  PyMODINIT_FUNC ;

/* Variables and functions */
 int /*<<< orphan*/ * Py_InitModule3 (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  import_array () ; 
 scalar_t__ load_module_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_methods ; 
 int /*<<< orphan*/  singleton_mod_state ; 

PyMODINIT_FUNC initdeepmind_lab(void) {
  PyObject* module =
      Py_InitModule3("deepmind_lab", module_methods, "DeepMind Lab API module");

  if (module != NULL && load_module_impl(module, &singleton_mod_state) == 0) {
    import_array();
  }
}