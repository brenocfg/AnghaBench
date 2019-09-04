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
 char const** environ ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_object () ; 
 int /*<<< orphan*/  jv_object_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_object_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char const*) ; 
 int /*<<< orphan*/  jv_string_sized (char const*,int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static jv
make_env(jv env)
{
  if (jv_is_valid(env))
    return jv_copy(env);
  jv r = jv_object();
  if (environ == NULL)
    return r;
  for (size_t i = 0; environ[i] != NULL; i++) {
    const char *eq;

    if ((eq = strchr(environ[i], '=')) == NULL)
      r = jv_object_delete(r, jv_string(environ[i]));
    else
      r = jv_object_set(r, jv_string_sized(environ[i], eq - environ[i]), jv_string(eq + 1));
  }
  return jv_copy(r);
}