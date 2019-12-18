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
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,char const*) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static jv jv_basename(jv name) {
  const char *s = jv_string_value(name);
  const char *p = strrchr(s, '/');
  if (!p)
    return name;
  jv res = jv_string_fmt("%s", p);
  jv_free(name);
  return res;
}