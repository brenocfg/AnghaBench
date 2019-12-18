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
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  _PC_PATH_MAX ; 
 char* _fullpath (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 char* jv_mem_alloc (int) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 
 int pathconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* realpath (int /*<<< orphan*/ ,char*) ; 

jv jq_realpath(jv path) {
  int path_max;
  char *buf = NULL;
#ifdef _PC_PATH_MAX
  path_max = pathconf(jv_string_value(path),_PC_PATH_MAX);
#else
  path_max = PATH_MAX;
#endif
  if (path_max > 0) {
     buf = jv_mem_alloc(path_max);
  }
#ifdef WIN32
  char *tmp = _fullpath(buf, jv_string_value(path), path_max);
#else
  char *tmp = realpath(jv_string_value(path), buf);
#endif
  if (tmp == NULL) {
    free(buf);
    return path;
  }
  jv_free(path);
  path = jv_string(tmp);
  free(tmp);
  return path;
}