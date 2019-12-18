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
 int /*<<< orphan*/  cmp_char ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  qsort (char*,int,int,int /*<<< orphan*/ ) ; 
 char* sp_str_alloc (int) ; 
 int strlen (char*) ; 

char *sp_sort (char *s) {
  int l = strlen (s);
  char *t = sp_str_alloc (l);
  if (t != 0) {
    memcpy (t, s, (l + 1) * sizeof (char));
    qsort (t, l, sizeof (char), cmp_char);
  }

  return t;
}