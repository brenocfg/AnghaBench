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
 int MAX_FIELDS ; 
 int MAX_LETTER_SIZE ; 
 int field_n ; 
 char** field_name ; 
 int* field_name_len ; 
 char** field_value ; 
 int* field_value_len ; 
 int sscanf (char*,char*,...) ; 
 int strlen (char*) ; 

int get_fields (char *l) {
  int n;
  int len = strlen (l);
  int add;
  field_n = -1;
  if (sscanf (l, "a:%d%n", &n, &add) != 1 || l[add] != ':' || l[add + 1] != '{' || l[len - 1] != '}' || n < 0 || n > MAX_FIELDS || len > 2 * MAX_LETTER_SIZE + 1000) {
    return -1;
  }
  int i, j = add + 2;
  for (i = 0; i < n; i++) {
    int clen;
    if (sscanf (l + j, "s:%d%n", &clen, &add) != 1 || l[j + add] != ':' || l[j + add + 1] != '"') {
      return -1;
    }
    j += add + 2;
    field_name[i] = l + j;
    field_name_len[i] = clen;

    j += clen;

    if (j >= len || l[j] != '"' || l[j + 1] != ';') {
      return -1;
    }
    j += 2;

    switch (l[j]) {
      case 'b':
        if (l[j + 1] == ':' && (l[j + 2] == '0' || l[j + 2] == '1') && l[j + 3] == ';') {
          l[j] = 'i';

          field_value[i] = l + j + 2;
          field_value_len[i] = 1;

          j += 4;
        } else {
          return -1;
        }
        break;
      case 'd': {
        double value;
        if (sscanf (l + j, "d:%lf%n", &value, &add) != 1 || add < 3 || l[j + add] != ';') {
          return -1;
        }
        field_value[i] = l + j + 2;
        field_value_len[i] = add - 2;

        j += add + 1;
        break;
      }
      case 'i':
        if (sscanf (l + j, "i:%d%n", &clen, &add) != 1 || add < 3 || l[j + add] != ';') {
          return -1;
        }
        field_value[i] = l + j + 2;
        field_value_len[i] = add - 2;

        j += add + 1;
        break;
      case 's':
        if (sscanf (l + j, "s:%d%n", &clen, &add) != 1 || l[j + add] != ':' || l[j + add + 1] != '"') {
          return -1;
        }
        j += add + 2;
        field_value[i] = l + j;
        field_value_len[i] = clen;

        j += clen;

        if (j >= len) {
          return -1;
        }

        if (l[j++] != '"') {
          return -1;
        }
        if (l[j++] != ';') {
          return -1;
        }
        break;
      default:
        return -1;
    }
  }

  if (j != len - 1) {
    return -1;
  }
  return field_n = n;
}