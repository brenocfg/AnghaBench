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
typedef  unsigned long long privacy_key_t ;

/* Variables and functions */
 unsigned int compute_crc32 (char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int parse_privacy_key (const char *text, privacy_key_t *res, int reqeol) {
  int i = 0, j;
  unsigned x, y;
  if (verbosity > 1) {
    fprintf (stderr, "parsing privacy key '%s', reqeol=%d\n", text, reqeol);
  }
  while ((text[i] | 0x20) >= 'a' && (text[i] | 0x20) <= 'z' && i <= 32) {
    i++;
  }
  if (i <= 0 || i == 32) {
    return -1;
  }
  j = i;
  if (text[j] >= '0' && text[j] <= '9') {
    y = 0;
    while (text[j] >= '0' && text[j] <= '9') {
      if (j >= 48 || y > 0x7fffffff / 10) {
        return -1;
      }
      y = y * 10 + (text[j] - '0');
      j++;
    }
  } else if (text[j] == '*') {
    y = ~0;
    j++;
  } else {
    if (text[j] != '_' && text[j] != ' ' && text[j] != ',' && text[j]) {
      return -1;
    }
    while ((signed char) text[j] >= '0') {
      j++;
      if (j >= 64) {
        return -1;
      }
    }
    y = compute_crc32 (text + i, j - i);
  }
  if (text[j]) {
    if (reqeol > 0) {
      return -1;
    }
    if (text[j] != ' ' && (text[j] != ',' || reqeol != -1)) {
      return -1;
    }
  }
  x = compute_crc32 (text, i);
  *res = (((unsigned long long) x) << 32) + y;
  if (verbosity > 1) {
    fprintf (stderr, "privacy key = %016llx\n", *res);
  }
  return j;
}