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
 unsigned long long make_secret () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,...) ; 

__attribute__((used)) static int extract_secret (const char* filename, unsigned long long *secret) {
  int i;
  unsigned long long x;
  char c;
  char s[4];
  memset (s, 0, 4);
  *secret = 0;
  if (sscanf (filename, "%c_%llx.%3s", &c, &x, s) == 3) {
    *secret = x << 32;
    *secret |= ((unsigned int) ((unsigned char) c)) << 24;
  } else if (sscanf (filename, "%llx.%3s", &x, s) == 2) {
    *secret = x << 24;
  } else {
    *secret = make_secret ();
    return 1;
  }
  for (i = 0; i < 3; i++) {
    *secret |= ((unsigned int) ((unsigned char) s[i])) << (8 * (2 - i));
  }
  return 0;
}