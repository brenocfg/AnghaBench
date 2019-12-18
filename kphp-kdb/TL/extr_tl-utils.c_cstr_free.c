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
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  tl_zzfree (char*,scalar_t__) ; 

void cstr_free (char **s) {
  char *p = *s;
  if (p) {
    tl_zzfree (p, strlen (p) + 1);
    *s = NULL;
  }
}