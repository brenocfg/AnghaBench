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

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char const* const) ; 
 int strlen (char const* const) ; 
 char* tl_zzmalloc (int) ; 

char *cstr_dup (const char *const input) {
  int l = strlen (input);
  char *p = tl_zzmalloc (l + 1);
  strcpy (p, input);
  return p;
}