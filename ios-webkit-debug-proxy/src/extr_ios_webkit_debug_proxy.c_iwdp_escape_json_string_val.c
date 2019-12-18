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
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const) ; 
 int strlen (char const*) ; 

char *iwdp_escape_json_string_val(const char *str) {
  int len = strlen(str);
  char* res = (char*)malloc(len * 6 + 1);

  int i, j;
  for (i = 0, j = 0; i < len; i++, j++) {
    if (str[i] >= 0 && str[i] < 32) {
      sprintf(res + j, "\\u%04d", str[i]);
      j += 5;
    } else {
      if (str[i] == '"' || str[i] == '\\') {
        res[j++] = '\\';
      }
      res[j] = str[i];
    }
  }
  res[j] = '\0';

  return res;
}