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
typedef  int /*<<< orphan*/  uint16_t ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 scalar_t__ UV_E2BIG ; 
 int UV_ENOSPC ; 
 int UV__INET6_ADDRSTRLEN ; 
 int inet_ntop4 (unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  memset (unsigned int*,char,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ uv__strscpy (char*,char*,size_t) ; 

__attribute__((used)) static int inet_ntop6(const unsigned char *src, char *dst, size_t size) {
  /*
   * Note that int32_t and int16_t need only be "at least" large enough
   * to contain a value of the specified size.  On some systems, like
   * Crays, there is no such thing as an integer variable with 16 bits.
   * Keep this in mind if you think this function should have been coded
   * to use pointer overlays.  All the world's not a VAX.
   */
  char tmp[UV__INET6_ADDRSTRLEN], *tp;
  struct { int base, len; } best, cur;
  unsigned int words[sizeof(struct in6_addr) / sizeof(uint16_t)];
  int i;

  /*
   * Preprocess:
   *  Copy the input (bytewise) array into a wordwise array.
   *  Find the longest run of 0x00's in src[] for :: shorthanding.
   */
  memset(words, '\0', sizeof words);
  for (i = 0; i < (int) sizeof(struct in6_addr); i++)
    words[i / 2] |= (src[i] << ((1 - (i % 2)) << 3));
  best.base = -1;
  best.len = 0;
  cur.base = -1;
  cur.len = 0;
  for (i = 0; i < (int) ARRAY_SIZE(words); i++) {
    if (words[i] == 0) {
      if (cur.base == -1)
        cur.base = i, cur.len = 1;
      else
        cur.len++;
    } else {
      if (cur.base != -1) {
        if (best.base == -1 || cur.len > best.len)
          best = cur;
        cur.base = -1;
      }
    }
  }
  if (cur.base != -1) {
    if (best.base == -1 || cur.len > best.len)
      best = cur;
  }
  if (best.base != -1 && best.len < 2)
    best.base = -1;

  /*
   * Format the result.
   */
  tp = tmp;
  for (i = 0; i < (int) ARRAY_SIZE(words); i++) {
    /* Are we inside the best run of 0x00's? */
    if (best.base != -1 && i >= best.base &&
        i < (best.base + best.len)) {
      if (i == best.base)
        *tp++ = ':';
      continue;
    }
    /* Are we following an initial run of 0x00s or any real hex? */
    if (i != 0)
      *tp++ = ':';
    /* Is this address an encapsulated IPv4? */
    if (i == 6 && best.base == 0 && (best.len == 6 ||
        (best.len == 7 && words[7] != 0x0001) ||
        (best.len == 5 && words[5] == 0xffff))) {
      int err = inet_ntop4(src+12, tp, sizeof tmp - (tp - tmp));
      if (err)
        return err;
      tp += strlen(tp);
      break;
    }
    tp += sprintf(tp, "%x", words[i]);
  }
  /* Was it a trailing run of 0x00's? */
  if (best.base != -1 && (best.base + best.len) == ARRAY_SIZE(words))
    *tp++ = ':';
  *tp++ = '\0';
  if (UV_E2BIG == uv__strscpy(dst, tmp, size))
    return UV_ENOSPC;
  return 0;
}