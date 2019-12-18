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
 int get_str_class (char const*,int) ; 
 int /*<<< orphan*/  lc_str (char*,char const*,int) ; 
 int stem_eng (char const*,char*,int) ; 
 int stem_rus_win1251 (char const*,int,int*) ; 
 int /*<<< orphan*/  use_stemmer ; 

int my_lc_str (char *buff, const char *text, int len) {
  int x, c;
  if (!use_stemmer || len < 3) {
    lc_str (buff, text, len);
    return len;
  }
  c = get_str_class (text, len);
  if ((c & 12) == 12) {
    int delete_penultimate_letter;
    x = stem_rus_win1251 (text, len, &delete_penultimate_letter);
    assert (x > 0 && x <= len);
    lc_str (buff, text, x);
    if (delete_penultimate_letter) {
      assert (x >= 2);
      x--;
      buff[x - 1] = buff[x];
    }
    return x;
  }
  if (c & 8) {
    int i;
    for (i = 0; i < len; i++) {
      if (text[i] < 0) {
        break;
      }
    }
    if (i < len) {
      lc_str (buff, text, len);
      return len;
    }
    x = stem_eng (text, buff, len);
    assert (x > 0 && x <= len);
    lc_str (buff, buff, x);
    return x;
  }
  lc_str (buff, text, len);
  return len;
}