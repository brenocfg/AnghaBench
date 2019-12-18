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
 int stem_eng (char const*,int,char*) ; 
 int stem_rus_win1251 (char const*,int,char*,int) ; 
 int /*<<< orphan*/  use_stemmer ; 

int my_lc_str (char *buff, const char *text, int len) {
  int x, c;
  if (!use_stemmer) {
    lc_str (buff, text, len);
    return len;
  }
  c = get_str_class (text, len);
  if ((c & 12) == 12) {
    x = stem_rus_win1251 (text, len, buff, 1);
    lc_str (buff, buff, x);
    return x;
  }
  if (c & 8) {
    int i;
    for (i = 0; i < len && text[i] >= 0; i++) {
    }
    if (i == len) {
      x = stem_eng (text, len, buff);
      assert (x > 0 && x <= len);
      lc_str (buff, buff, x);
      return x;
    }
  }
  lc_str (buff, text, len);
  return len;
}