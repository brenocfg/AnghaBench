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
 int /*<<< orphan*/  black_list ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  prepare_str (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trie_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trie_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verbosity ; 

void black_list_set_string (char *buff, int f) {
  if (verbosity > 2) {
    fprintf (stderr, "set %d string <%s>\n", f, buff);
  }
  int size = strlen (buff);
  char *s = buff;
  int i;
  char t;
  for (i = 0; i <= size; i++) {
    if (buff[i] == '\t' || buff[i] == 0) {
      t = buff[i];
      buff[i] = 0;
      if (*s) {
        if (f) {
          trie_del (black_list, prepare_str (s, 1));
        } else {
          trie_add (&black_list, prepare_str (s, 1));
        }
      }
      if (verbosity > 2) {
        fprintf (stderr, " -- <%s>\n", s);
      }
      s = buff + i + 1;
      buff[i] = t;
    }
  }
}