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
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 long long strtoll (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int classify_suffix (char *suffix, int suffix_len, long long *MMPos) {
  int c = 0;
  MMPos[0] = MMPos[1] = 0;
  if (!*suffix) {
    return 1;
  }
  if (*suffix != '.') {
    return -1;
  }
  int i = 1;
  while (suffix[i] >= '0' && suffix[i] <= '9') {
    i++;
  }
  if (i > 1) {
    if (i < 7) {
      return -1;
    }
    int power = (suffix[1] - '0') * 10 + (suffix[2] - '0');
    if (power > 18) {
      return -1;
    }

    long long base = strtoll (suffix + 3, 0, 10);

    int cnt = power - (i - 7);
    if (cnt < 0) {
      return -1;
    }

    if (power > 0 && suffix[3] == '0') {
      return -1;
    }

    MMPos[0] = base;
    MMPos[1] = base;

    int j;
    for (j = 0; j < cnt; j++) {
      MMPos[0] *= 10;
      MMPos[1] = MMPos[1] * 10 + 9;
    }

    suffix += i;
    if (!*suffix) {
      return 5;
    }
    if (*suffix != '.') {
      return -1;
    }
    c = 4;
  } else {
    MMPos[0] = 0;
    MMPos[1] = (1LL << 62);
  }

  switch (suffix[1]) {
  case 'b':
    if (!strcmp (suffix, ".bin")) {
      return c;
    }
    return strcmp (suffix, ".bin.bz") ? -1 : (c + 16);
  case 'e':
    return strcmp (suffix, ".enc") ? -1 : c + 32;
  case 't':
    return strcmp (suffix, ".tmp") ? -1 : c + 3;
  }
  return -1;
}