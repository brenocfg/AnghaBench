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
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  dyn_mark_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int check_word (char*,int) ; 
 int /*<<< orphan*/ * check_word_stat ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_re (char*,int /*<<< orphan*/ *) ; 
 int get_notword (char*) ; 
 int get_word (char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int my_lc_str (char*,char*,int) ; 
 int /*<<< orphan*/  re_email ; 
 int /*<<< orphan*/  re_url ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 char* zmalloc (scalar_t__) ; 

int spell_check (char *original_text, int res[3], int destroy_original) {
  static char buff[16384];
  memset (res, 0, sizeof (res));
  char *text;
  dyn_mark_t m;
  if (!destroy_original) {
    dyn_mark (m);
    text = zmalloc (strlen (original_text) + 1);
    strcpy (text, original_text);
  } else {
    text = original_text;
  }
  vkprintf (3, "Before filter: %s\n", text);
  filter_re (text, &re_email);
  filter_re (text, &re_url);
  vkprintf (3, "After filter: %s\n", text);

  while (*text) {
    int wl = get_notword (text);
    if (wl < 0) {
      break;
    }
    text += wl;
    wl = get_word (text);
    if (!wl) {
      continue;
    }
    assert (wl > 0 && wl < 16383);
    my_lc_str (buff, text, wl);
    if (wl >= 3) {
      int l = my_lc_str (buff, text, wl);
      int r = check_word (buff, l);
      vkprintf (3, "[%d] check_word: %.*s\n", r, l, buff);
      if (r >= 0) {
        check_word_stat[1]++;
        if (r) {
          res[0]++;
          check_word_stat[0]++;
        } else {
          res[1]++;
        }
      } else {
        res[2]++;
      }
    }
    text += wl;
  }
  if (!destroy_original) {
    dyn_release (m);
  }
  return 0;
}