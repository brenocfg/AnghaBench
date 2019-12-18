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
 int PathIsRelativeA (char const*) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int path_is_relative(jv p) {
  const char *s = jv_string_value(p);

#ifdef WIN32
  int res = PathIsRelativeA(s);
#else
  int res = *s != '/';
#endif
  jv_free(p);
  return res;
}