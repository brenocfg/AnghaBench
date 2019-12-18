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
 int /*<<< orphan*/  good_string_to_utf8 (unsigned char*,int*) ; 
 int remove_diacritics (int) ; 

void bayes_string_to_utf8 (unsigned char *s, int *v) {
  good_string_to_utf8 (s, v);

  int i;
  for (i = 0; v[i]; i++) {
    v[i] = remove_diacritics (v[i]);
  }

/*
  int j;
  for (i = j = 0; v[i]; i++) {
    if (v[i + 1] == '#' && (v[i] == '&' || v[i] == '$')) {
      int r = 0, ti = i;
      if (v[i + 2] != 'x') {
        for (i += 2; v[i] != ';' && v[i]; i++) {
          if ('0' <= v[i] && v[i]<='9') {
            r = r * 10 + v[i] - '0';
          } else {
            break;
          }
        }
      } else {
        for (i += 3; v[i] != ';' && v[i]; i++) {
          if (('0' <= v[i] && v[i]<='9') ||
              ('a' <= v[i] && v[i] <= 'f') ||
              ('A' <= v[i] && v[i] <= 'F')) {
            r = r * 16;
            if (v[i] <= '9') {
              r += v[i] -'0';
            } else if (v[i] <= 'F') {
              r += v[i] -'A' + 10;
            } else {
              r += v[i] -'a' + 10;
            }
          } else {
            break;
          }
        }
      }
      if (r == 0) {
        v[j++] = v[i = ti];
      } else {
        v[j++] = r;
        if (v[i] != ';') {
          i--;
        }
      }
    } else if (v[i] == '%' && '0' <= v[i + 1] && v[i + 1] <= '7' &&
                            (('0' <= v[i + 2] && v[i + 2] <= '9') ||
                             ('a' <= v[i + 2] && v[i + 2] <= 'f') ||
                             ('A' <= v[i + 2] && v[i + 2] <= 'F'))) {
      int r;
      if (v[i + 2] <= '9') {
        r = v[i + 2] -'0';
      } else if (v[i + 2] <= 'F') {
        r = v[i + 2] -'A' + 10;
      } else {
        r = v[i + 2] -'a' + 10;
      }
      r += (v[i + 1] - '0') * 16;
      i += 2;
      v[j++] = r;
    } else {
      v[j++] = v[i];
    }
  }
  v[j++] = 0;*/
}