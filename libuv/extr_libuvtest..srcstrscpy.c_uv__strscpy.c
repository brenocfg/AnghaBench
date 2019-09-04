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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t SSIZE_MAX ; 
 int /*<<< orphan*/  UV_E2BIG ; 

ssize_t uv__strscpy(char* d, const char* s, size_t n) {
  size_t i;

  for (i = 0; i < n; i++)
    if ('\0' == (d[i] = s[i]))
      return i > SSIZE_MAX ? UV_E2BIG : (ssize_t) i;

  if (i == 0)
    return 0;

  d[--i] = '\0';

  return UV_E2BIG;
}