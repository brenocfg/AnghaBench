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
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int strlen (char const* const) ; 
 scalar_t__* url_symbols64 ; 

int base64url_decode (const char *const input, unsigned char *output, int olen) {
  static int tbl_url_symbols64_initialized = 0;
  static char tbl_url_symbols64[256];
  int ilen = strlen (input);
  int i, j = 0;
  if (!tbl_url_symbols64_initialized) {
    memset (tbl_url_symbols64, 0xff, 256);
    for (i = 0; i < 64; i++) {
      tbl_url_symbols64[(int) url_symbols64[i]] = i; 
    }
    tbl_url_symbols64_initialized = 1;
  }
  char buf[3];
  for (i = 0; i < ilen; i += 4) {
    int o = 0, l = 3, u = 0;
    do {
      if (i + u >= ilen) {
        switch (u) {
          case 0:
          case 1:
            return -4;
          case 2:
            o <<= 12;
            l = 1;
            break;
          case 3:
            o <<= 6;
            l = 2;
            break;
        }
        break;
      }
      int c = tbl_url_symbols64[(unsigned char) input[i+u]];
      if (c < 0) {
        return -3;
      }
      o <<= 6;
      o |= c;
    } while (++u < 4);
    u = 2;
    do {
      buf[u] = o & 255;
      o >>= 8;
    } while (--u >= 0);
    if (j + l > olen) {
      return -1;
    }
    memcpy (&output[j], buf, l);
    j += l;
  }
  return j;
}