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
 int /*<<< orphan*/  string_to_utf8 (unsigned char const*,int*) ; 

void good_string_to_utf8 (const unsigned char *s, int *v) {
  string_to_utf8 (s, v);

  int i, j;
  for (i = j = 0; v[i]; i++) {
    if (v[i] == '&') {
      if (v[i + 1] == 'a' && v[i + 2] == 'm' && v[i + 3] == 'p' && v[i + 4] == ';') {
        i += 4, v[j++] = '&';
      } else if (v[i + 1] == 'l' && v[i + 2] == 't' && v[i + 3] == ';') {
        i += 3, v[j++] = '<';
      } else if (v[i + 1] == 'g' && v[i + 2] == 't' && v[i + 3] == ';') {
        i += 3, v[j++] = '>';
      } else if (v[i + 1] == 'q' && v[i + 2] == 'u' && v[i + 3] == 'o' && v[i + 4] == 't' && v[i + 5] == ';') {
        i += 5, v[j++] = '"';
      } else {
        v[j++] = '&';
      }
    } else {
      v[j++] = v[i];
    }
  }
  v[j++] = 0;

  for (i = j = 0; v[i]; i++) {
    if (v[i] == '&') {
      if (v[i + 1] == 'a' && v[i + 2] == 'm' && v[i + 3] == 'p' && v[i + 4] == ';') {
        i += 4, v[j++] = '&';
      } else if (v[i + 1] == '#') {
        int r = 0, ti = i;
        for (i += 2; v[i]!=';' && v[i]; i++) {
          if ('0' <= v[i] && v[i] <= '9') {
            r = r * 10 + v[i] - '0';
          } else {
            break;
          }
        }
        if (v[i] != ';') {
          v[j++] = v[i = ti];
        } else {
          v[j++] = r;
        }
      } else {
        v[j++] = v[i];
      }
    } else {
      v[j++] = v[i];
    }
  }
  v[j++] = 0;

  for (i = j = 0; v[i]; i++) {
    if (v[i] !=   173 && (v[i] < 65024 || v[i] > 65062) && (v[i] < 7627 || v[i] > 7654) &&
        v[i] !=  8288 && (v[i] <  8202 || v[i] >  8207) && (v[i] < 8400 || v[i] > 8433) &&
        v[i] !=  8228 && (v[i] <  8298 || v[i] >  8303) &&
        v[i] != 65279 && (v[i] <   768 || v[i] >   879)) {
      v[j++] = v[i];
    }
  }
  v[j++] = 0;
}