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
 scalar_t__ strlen (char const* const) ; 
 char* zmalloc (scalar_t__) ; 

char *zstrdup (const char *const s) {
  char *p = zmalloc (strlen (s) + 1);
  strcpy (p, s);
  return p;
}