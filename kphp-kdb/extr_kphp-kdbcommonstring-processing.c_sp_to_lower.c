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
 char* sp_str_alloc (int) ; 
 int strlen (char*) ; 
 char to_lower (char) ; 

char *sp_to_lower (char *s) {
  int l = strlen (s);
  char *t = sp_str_alloc (l);
  if (t != 0) {
    int i;
    for (i = 0; i <= l; i++) {
      t[i] = to_lower (s[i]);
    }
  }

  return t;
}