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
typedef  int /*<<< orphan*/  jq_state ;

/* Variables and functions */
 int INT_MAX ; 
 char** environ ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_null () ; 
 int /*<<< orphan*/  jv_object () ; 
 int /*<<< orphan*/  jv_object_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char const*) ; 
 int /*<<< orphan*/  jv_string_sized (char const*,int) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static jv f_env(jq_state *jq, jv input) {
  jv_free(input);
  jv env = jv_object();
  const char *var, *val;
  for (char **e = environ; *e != NULL; e++) {
    var = e[0];
    val = strchr(e[0], '=');
    if (val == NULL)
      env = jv_object_set(env, jv_string(var), jv_null());
    else if (var - val < INT_MAX)
      env = jv_object_set(env, jv_string_sized(var, val - var), jv_string(val + 1));
  }
  return env;
}