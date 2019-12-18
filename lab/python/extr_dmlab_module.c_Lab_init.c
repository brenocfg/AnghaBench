#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ (* setting ) (int /*<<< orphan*/ ,char*,char*) ;char const* (* error_message ) (int /*<<< orphan*/ ) ;scalar_t__ (* init ) (int /*<<< orphan*/ ) ;int (* observation_count ) (int /*<<< orphan*/ ) ;char* (* observation_name ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  runfiles_path; } ;
struct TYPE_7__ {int /*<<< orphan*/ * write_level_to_cache; int /*<<< orphan*/ * fetch_level_from_cache; int /*<<< orphan*/ * context; } ;
struct TYPE_9__ {char* optional_temp_folder; TYPE_1__ level_cache_params; int /*<<< orphan*/  renderer; int /*<<< orphan*/  runfiles_path; } ;
struct TYPE_8__ {int observation_count; int* observation_indices; int /*<<< orphan*/  context; TYPE_6__* env_c_api; scalar_t__ episode; int /*<<< orphan*/  status; int /*<<< orphan*/ * level_cache_context; } ;
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ LabObject ;
typedef  TYPE_3__ DeepMindLabLaunchParams ;

/* Variables and functions */
 int /*<<< orphan*/  DeepMindLabRenderer_Hardware ; 
 int /*<<< orphan*/  DeepMindLabRenderer_Software ; 
 int /*<<< orphan*/  ENV_STATUS_UNINITIALIZED ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char**,int /*<<< orphan*/ **,char**) ; 
 scalar_t__ PyDict_Next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyDict_Type ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyImport_AddModule (char*) ; 
 int /*<<< orphan*/ * PyList_GetItem (int /*<<< orphan*/ *,int) ; 
 int PyList_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyList_Type ; 
 char* PyString_AsString (int /*<<< orphan*/ *) ; 
 char* PyUnicode_AsUTF8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int* calloc (int,int) ; 
 scalar_t__ dmlab_connect (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetch_level_from_cache ; 
 TYPE_4__* get_module_state (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*,char*) ; 
 char const* stub10 (int /*<<< orphan*/ ) ; 
 int stub11 (int /*<<< orphan*/ ) ; 
 char* stub12 (int /*<<< orphan*/ ,int) ; 
 char const* stub2 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,char*,char*) ; 
 char const* stub4 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,char*,char*) ; 
 char const* stub6 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub7 (int /*<<< orphan*/ ,char const*,char const*) ; 
 char const* stub8 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub9 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_level_to_cache ; 

__attribute__((used)) static int Lab_init(PyObject* pself, PyObject* args, PyObject* kwds) {
  LabObject* self = (LabObject*)pself;
  char* level;
  char* renderer = NULL;
  char* temp_folder = NULL;
  PyObject *observations = NULL, *config = NULL, *level_cache = NULL;

  static char* kwlist[] = {
    "level",
    "observations",
    "config",
    "renderer",
    "level_cache",
    "temp_folder",
    NULL
  };

  if (self->env_c_api == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "RL API not setup");
    return -1;
  }

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "sO!|O!sOs", kwlist,
                                   &level,
                                   &PyList_Type, &observations,
                                   &PyDict_Type, &config,
                                   &renderer, &level_cache, &temp_folder)) {
    return -1;
  }

  self->observation_count = PyList_Size(observations);
  self->observation_indices = calloc(self->observation_count, sizeof(int));
  if (self->observation_indices == NULL) {
    PyErr_NoMemory();
    return -1;
  }
  {
#if PY_MAJOR_VERSION >= 3
    PyObject* module =
        PyImport_AddModule("deepmind_lab");
    if (module == NULL) {
      PyErr_SetString(PyExc_RuntimeError, "deepmind_lab module not loaded");
      return -1;
    }
#else  // PY_MAJOR_VERSION >= 3
    PyObject* module = NULL;
#endif  // PY_MAJOR_VERSION >= 3

    DeepMindLabLaunchParams params = {};
    params.runfiles_path = get_module_state(module)->runfiles_path;
    params.renderer = DeepMindLabRenderer_Software;
    if (renderer != NULL && renderer[0] != '\0') {
      if (strcmp(renderer, "hardware") == 0) {
        params.renderer = DeepMindLabRenderer_Hardware;
      } else if (strcmp(renderer, "software") != 0) {
        PyErr_Format(PyExc_RuntimeError,
                     "Failed to set renderer must be \"hardware\" or "
                     "\"software\" actual \"%s\"!",
                     renderer);
        return -1;
      }
    }

    if (level_cache != NULL && level_cache != Py_None) {
      Py_INCREF(level_cache);
      params.level_cache_params.context = level_cache;
      params.level_cache_params.fetch_level_from_cache =
          &fetch_level_from_cache;
      params.level_cache_params.write_level_to_cache = &write_level_to_cache;
      self->level_cache_context = level_cache;
    }

    if (temp_folder != NULL) {
      params.optional_temp_folder = temp_folder;
    }

    if (dmlab_connect(&params, self->env_c_api, &self->context) != 0) {
      PyErr_SetString(PyExc_RuntimeError, "Failed to connect RL API");
      return -1;
    }

// When running under TSAN, switch to the interpreted VM, which is
// instrumentable.
//
// It might be a better idea add __attribute__((no_sanitize("thread"))) to
// vm_x86.c, but I have not managed to make that work.
#ifndef __has_feature
#  define __has_feature(x) 0
#endif
#if __has_feature(thread_sanitizer)
    if (self->env_c_api->setting(self->context, "vmMode", "interpreted") != 0) {
      PyErr_Format(PyExc_RuntimeError,
                   "Failed to apply 'vmMode' setting - \"%s\"",
                   self->env_c_api->error_message(self->context));
      return -1;
    }
#endif
    self->status = ENV_STATUS_UNINITIALIZED;
    self->episode = 0;
  }

  if (self->env_c_api->setting(self->context, "levelName", level) != 0) {
    PyErr_Format(PyExc_RuntimeError, "Invalid levelName flag '%s' - \"%s\"",
                 level, self->env_c_api->error_message(self->context));
    return -1;
  }

  if (self->env_c_api->setting(self->context, "fps", "60") != 0) {
    PyErr_Format(PyExc_RuntimeError, "Failed to set fps - \"%s\"",
                 self->env_c_api->error_message(self->context));
    return -1;
  }

  if (config != NULL) {
    PyObject *pykey, *pyvalue;
    Py_ssize_t pos = 0;
    const char *key, *value;

    while (PyDict_Next(config, &pos, &pykey, &pyvalue)) {
#if PY_MAJOR_VERSION >= 3
      key = PyUnicode_AsUTF8(pykey);
      value = PyUnicode_AsUTF8(pyvalue);
#else  // PY_MAJOR_VERSION >= 3
      key = PyString_AsString(pykey);
      value = PyString_AsString(pyvalue);
#endif  // PY_MAJOR_VERSION >= 3
      if (key == NULL || value == NULL) {
        return -1;
      }
      if (self->env_c_api->setting(self->context, key, value) != 0) {
        PyErr_Format(PyExc_RuntimeError,
                     "Failed to apply setting '%s = %s' - \"%s\"", key, value,
                     self->env_c_api->error_message(self->context));
        return -1;
      }
    }
  }

  if (self->env_c_api->init(self->context) != 0) {
    PyErr_Format(PyExc_RuntimeError, "Failed to init environment - \"%s\"",
                 self->env_c_api->error_message(self->context));
    return -1;
  }

  const char* observation_name;
  int api_observation_count = self->env_c_api->observation_count(self->context);
  for (int i = 0; i < self->observation_count; ++i) {
#if PY_MAJOR_VERSION >= 3
    observation_name = PyUnicode_AsUTF8(PyList_GetItem(observations, i));
#else  // PY_MAJOR_VERSION >= 3
    observation_name = PyString_AsString(PyList_GetItem(observations, i));
#endif  // PY_MAJOR_VERSION >= 3
    if (observation_name == NULL) {
      return -1;
    }
    int j;
    for (j = 0; j < api_observation_count; ++j) {
      if (strcmp(self->env_c_api->observation_name(self->context, j),
                 observation_name) == 0) {
        self->observation_indices[i] = j;
        break;
      }
    }
    if (j == api_observation_count) {
      PyErr_Format(PyExc_ValueError, "Unknown observation '%s'.",
                   observation_name);
      return -1;
    }
  }

  return 0;
}