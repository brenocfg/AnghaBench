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
 scalar_t__ MAX_NAME_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int get_notword (char*) ; 
 int get_word (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int my_lc_str (char*,char*,int) ; 
 char* prep_buf ; 
 char* prep_buf_res ; 
 char* prepare_str_cp1251 (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 

char *prepare_watchcat_str (char *x, int uni) {
  if (strlen (x) >= MAX_NAME_SIZE) {
    return NULL;
  }

//  fprintf (stderr, "prepare\n%s\n", x);

  char delim = uni ? ' ' : '+';

  char *s = prep_buf;
  /* copypaste from search-data.c */
  int no_nw = 1;
  const char *prev = 0;
  while (*x) {
    if (x == prev) {
      fprintf (stderr, "error at %.30s\n", x);
      exit (2);
    }
    prev = x - no_nw;
    int wl = no_nw ? 0 : get_notword (x);
    no_nw = 0;
    if (wl < 0) {
      break;
    }
    while (wl > 0 && *x != 0x1f) {
      x++;
      wl--;
    }
    if (*x == 0x1f) {
      wl = 1;
      while ((unsigned char) x[wl] >= 0x40) {
        wl++;
      }
      no_nw = 1;
    } else {
      wl = get_word (x);
    }
    if (!wl) {
      continue;
    }
    assert (wl > 0 && wl < 511);
    if (*x != 0x1f) {//TODO why not s += my_lc_str (s, x, wl);
      int len = my_lc_str (prep_buf_res, x, wl);
      memcpy (s, prep_buf_res, len);
      s += len;
    } else {
      memcpy (s, x, wl);
      s += wl;
    }
    *s++ = delim;

    x += wl;
  }
  *s = 0;

//  memcpy (prep_buf, x, strlen (x) + 1);

  char *v = uni ? prepare_str_cp1251 (prep_buf) : prep_buf;

//  fprintf (stderr, "%s\n--------------------------\n", v);
  return v;
}