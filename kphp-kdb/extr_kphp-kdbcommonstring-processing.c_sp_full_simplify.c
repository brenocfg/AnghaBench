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
 int /*<<< orphan*/  assert (int) ; 
 char conv_letter (char) ; 
 int /*<<< orphan*/  next_character (char const*,int*) ; 
 char simplify (int /*<<< orphan*/ ) ; 
 char* sp_str_alloc (int) ; 
 char* sp_str_pre_alloc (int) ; 
 int strlen (char const*) ; 

char *sp_full_simplify (const char *s) {
  int l = strlen (s);
  char *t = sp_str_pre_alloc (l);
  if (t != 0) {
    int nl = 0, i;
    for (i = 0; i < l; i++) {
      char c = simplify (next_character (s, &i));
      if (c != 0) {
        t[nl++] = conv_letter (c);
      }
    }
    t[nl] = 0;

    char *new_t = sp_str_alloc (nl);
    assert (t == new_t);
  }

  return t;
}