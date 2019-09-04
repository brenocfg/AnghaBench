#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  runfiles_path; } ;
typedef  int /*<<< orphan*/  PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LabModuleState ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyModule_AddObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ PyType_Ready (int /*<<< orphan*/ *) ; 
 char* Py_GetProgramFullPath () ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deepmind_lab_LabType ; 
 TYPE_1__* get_module_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int load_module_impl(PyObject* module, LabModuleState* state) {
#if PY_MAJOR_VERSION >= 3
  PyTypeObject* lab_type = malloc(sizeof(PyTypeObject));
  memcpy(lab_type, &deepmind_lab_LabType, sizeof(PyTypeObject));
#else  // PY_MAJOR_VERSION >= 3
  PyTypeObject* lab_type = &deepmind_lab_LabType;
#endif  // PY_MAJOR_VERSION >= 3
  if (PyType_Ready(lab_type) < 0) return -1;
  Py_INCREF(lab_type);
  PyModule_AddObject(module, "Lab", (PyObject*)lab_type);

#ifdef DEEPMIND_LAB_MODULE_RUNFILES_DIR
  PyObject *v = PyObject_GetAttrString(module, "__file__");
#if PY_MAJOR_VERSION >= 3
  if (v && PyUnicode_Check(v)) {
    Py_ssize_t len;
    const char* file = PyUnicode_AsUTF8AndSize(v, &len);
    if (len < sizeof(state->runfiles_path)) {
#else  // PY_MAJOR_VERSION >= 3
  if (v && PyString_Check(v)) {
    const char* file = PyString_AsString(v);
    if (strlen(file) < sizeof(state->runfiles_path)) {
#endif  // PY_MAJOR_VERSION >= 3
      strcpy(state->runfiles_path, file);
    } else {
      PyErr_SetString(PyExc_RuntimeError, "Runfiles directory name too long!");
      return -1;
    }

    char* last_slash = strrchr(state->runfiles_path, '/');
    if (last_slash != NULL) {
      *last_slash = '\0';
    } else {
      PyErr_SetString(PyExc_RuntimeError,
                      "Unable to determine runfiles directory!");
      return -1;
    }
  } else {
    fprintf(stderr, "Failed to get __file__ attribute.\n");
    PyErr_Clear();
    strcpy(state->runfiles_path, ".");
  }
#else  // DEEPMIND_LAB_MODULE_RUNFILES_DIR
  static const char kRunfiles[] = ".runfiles/org_deepmind_lab";
  LabModuleState* module_state = get_module_state(module);

#if PY_MAJOR_VERSION >= 3
  PyObject* u = PyUnicode_FromWideChar(Py_GetProgramFullPath(), -1);
  if (u == NULL) return -1;
  Py_ssize_t n;
  const char* s = PyUnicode_AsUTF8AndSize(u, &n);
  if (n + strlen(kRunfiles) < sizeof(module_state->runfiles_path)) {
    strcpy(module_state->runfiles_path, s);
    strcat(module_state->runfiles_path, kRunfiles);
    Py_DECREF(u);
  } else {
    Py_DECREF(u);
#else  // PY_MAJOR_VERSION >= 3
  const char* s = Py_GetProgramFullPath();
  size_t n = strlen(s);
  if (n + strlen(kRunfiles) < sizeof(module_state->runfiles_path)) {
    strcpy(module_state->runfiles_path, s);
    strcat(module_state->runfiles_path, kRunfiles);
  } else {
#endif  // PY_MAJOR_VERSION >= 3
    PyErr_SetString(PyExc_RuntimeError, "Runfiles directory name too long!");
    return -1;
  }

#endif  // DEEPMIND_LAB_MODULE_RUNFILES_DIR

  srand(time(NULL));
  return 0;
}