#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; } ;
typedef  TYPE_1__ type_desc ;

/* Variables and functions */
 scalar_t__ MAX_FIELDS ; 
 int MAX_RETURN_FIELDS ; 
 scalar_t__ get_field_id_len (TYPE_1__*,char*,int) ; 
 scalar_t__* return_fields ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int get_fields (type_desc *t, char *fields) {
  if (!fields[0]) {
    return 0;
  }

  int i = 0, j, res = 0;
  for (j = i; (j == 0 || fields[j - 1] == ',') && res < MAX_RETURN_FIELDS; i = ++j) {
    while (fields[j] != ',' && fields[j]) {
      j++;
    }
//    dbg ("  look for (field = <%s>)\n", fields + i);
    return_fields[res] = get_field_id_len (t, fields + i, j - i);
    if (return_fields[res] < 0) {
      if ((!strncmp (fields + i, "location", 8) || !strncmp (fields + i, "original_location", 17)) && t->name[0] == 'p') {
        int add = 0;
        if (fields[i] == 'o') {
          i += 9;
          add = 128;
        }

        if (j - i == 8) {
          return_fields[res++] = MAX_FIELDS + add;
        } else {
          if (j - i > 26 + 8 + 1) {
            return -1;
          }
          i += 8;
          int t = j, rotate = 0;
          if ('0' <= fields[t - 1] && fields[t - 1] <= '3') {
            t--;
            rotate = fields[t] - '0';
          }
          if (i == t) {
            return -1;
          }
          while (i != t && res < MAX_RETURN_FIELDS) {
            if (fields[i] < 'a' || fields[i] > 'z') {
              return -1;
            }
            return_fields[res++] = MAX_FIELDS + add + (fields[i++] - 'a' + 1) + (rotate << 5);
          }
        }
      } else if (j - i == 8 && !strncmp (fields + i, "ordering", 8)) {
        return_fields[res++] = MAX_FIELDS + 256;
      } else {
        return -1;
      }
    } else {
      res++;
    }
  }
  return res;
}