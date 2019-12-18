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
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int UV_EINVAL ; 
 int inet_pton4 (char const*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 char* strchr (char const*,int) ; 

__attribute__((used)) static int inet_pton6(const char *src, unsigned char *dst) {
  static const char xdigits_l[] = "0123456789abcdef",
                    xdigits_u[] = "0123456789ABCDEF";
  unsigned char tmp[sizeof(struct in6_addr)], *tp, *endp, *colonp;
  const char *xdigits, *curtok;
  int ch, seen_xdigits;
  unsigned int val;

  memset((tp = tmp), '\0', sizeof tmp);
  endp = tp + sizeof tmp;
  colonp = NULL;
  /* Leading :: requires some special handling. */
  if (*src == ':')
    if (*++src != ':')
      return UV_EINVAL;
  curtok = src;
  seen_xdigits = 0;
  val = 0;
  while ((ch = *src++) != '\0') {
    const char *pch;

    if ((pch = strchr((xdigits = xdigits_l), ch)) == NULL)
      pch = strchr((xdigits = xdigits_u), ch);
    if (pch != NULL) {
      val <<= 4;
      val |= (pch - xdigits);
      if (++seen_xdigits > 4)
        return UV_EINVAL;
      continue;
    }
    if (ch == ':') {
      curtok = src;
      if (!seen_xdigits) {
        if (colonp)
          return UV_EINVAL;
        colonp = tp;
        continue;
      } else if (*src == '\0') {
        return UV_EINVAL;
      }
      if (tp + sizeof(uint16_t) > endp)
        return UV_EINVAL;
      *tp++ = (unsigned char) (val >> 8) & 0xff;
      *tp++ = (unsigned char) val & 0xff;
      seen_xdigits = 0;
      val = 0;
      continue;
    }
    if (ch == '.' && ((tp + sizeof(struct in_addr)) <= endp)) {
      int err = inet_pton4(curtok, tp);
      if (err == 0) {
        tp += sizeof(struct in_addr);
        seen_xdigits = 0;
        break;  /*%< '\\0' was seen by inet_pton4(). */
      }
    }
    return UV_EINVAL;
  }
  if (seen_xdigits) {
    if (tp + sizeof(uint16_t) > endp)
      return UV_EINVAL;
    *tp++ = (unsigned char) (val >> 8) & 0xff;
    *tp++ = (unsigned char) val & 0xff;
  }
  if (colonp != NULL) {
    /*
     * Since some memmove()'s erroneously fail to handle
     * overlapping regions, we'll do the shift by hand.
     */
    const int n = tp - colonp;
    int i;

    if (tp == endp)
      return UV_EINVAL;
    for (i = 1; i <= n; i++) {
      endp[- i] = colonp[n - i];
      colonp[n - i] = 0;
    }
    tp = endp;
  }
  if (tp != endp)
    return UV_EINVAL;
  memcpy(dst, tmp, sizeof tmp);
  return 0;
}