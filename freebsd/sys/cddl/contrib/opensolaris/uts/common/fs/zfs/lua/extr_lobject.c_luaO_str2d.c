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
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/  cast_uchar (char) ; 
 scalar_t__ lisspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_str2number (char const*,char**) ; 
 int /*<<< orphan*/  lua_strx2number (char const*,char**) ; 
 scalar_t__ strpbrk (char const*,char*) ; 

int luaO_str2d (const char *s, size_t len, lua_Number *result) {
  char *endptr;
  if (strpbrk(s, "nN"))  /* reject 'inf' and 'nan' */
    return 0;
  else if (strpbrk(s, "xX"))  /* hexa? */
    *result = lua_strx2number(s, &endptr);
  else
    *result = lua_str2number(s, &endptr);
  if (endptr == s) return 0;  /* nothing recognized */
  while (lisspace(cast_uchar(*endptr))) endptr++;
  return (endptr == s + len);  /* OK if no trailing characters */
}