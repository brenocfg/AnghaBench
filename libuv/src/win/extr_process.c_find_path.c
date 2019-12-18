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
typedef  scalar_t__ WCHAR ;

/* Variables and functions */
 scalar_t__ wcslen (scalar_t__*) ; 

__attribute__((used)) static WCHAR* find_path(WCHAR *env) {
  for (; env != NULL && *env != 0; env += wcslen(env) + 1) {
    if ((env[0] == L'P' || env[0] == L'p') &&
        (env[1] == L'A' || env[1] == L'a') &&
        (env[2] == L'T' || env[2] == L't') &&
        (env[3] == L'H' || env[3] == L'h') &&
        (env[4] == L'=')) {
      return &env[5];
    }
  }

  return NULL;
}