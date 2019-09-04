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
typedef  int uint32_t ;

/* Variables and functions */
#define  UTF8_INVAL 129 
#define  UTF8_VALID 128 
 int utf8_decode (int*,int*,unsigned char) ; 
 char* xcalloc (int,int) ; 

__attribute__((used)) static char *
sanitize_utf8 (const char *str, int len)
{
  char *buf = NULL;
  uint32_t state = UTF8_VALID, prev = UTF8_VALID, cp = 0;
  int i = 0, j = 0, k = 0, l = 0;

  buf = xcalloc (len + 1, sizeof (char));
  for (; i < len; prev = state, ++i) {
    switch (utf8_decode (&state, &cp, (unsigned char) str[i])) {
    case UTF8_INVAL:
      /* replace the whole sequence */
      if (k) {
        for (l = i - k; l < i; ++l)
          buf[j++] = '?';
      } else {
        buf[j++] = '?';
      }
      state = UTF8_VALID;
      if (prev != UTF8_VALID)
        i--;
      k = 0;
      break;
    case UTF8_VALID:
      /* fill i - k valid continuation bytes */
      if (k)
        for (l = i - k; l < i; ++l)
          buf[j++] = str[l];
      buf[j++] = str[i];
      k = 0;
      break;
    default:
      /* UTF8_VALID + continuation bytes */
      k++;
      break;
    }
  }

  return buf;
}