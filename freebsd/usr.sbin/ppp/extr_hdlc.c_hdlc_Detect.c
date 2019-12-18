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
typedef  int /*<<< orphan*/  u_char ;
struct frameheader {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 struct frameheader* FrameHeaders ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

int
hdlc_Detect(u_char const **cp, unsigned n, int issync)
{
  const struct frameheader *fh;
  const u_char *h;
  size_t len, cmp;

  while (n) {
    for (fh = FrameHeaders; fh->len; fh++) {
      h = issync ? fh->data + 1 : fh->data;
      len = issync ? fh->len - 1 : fh->len;
      cmp = n >= len ? len : n;
      if (memcmp(*cp, h, cmp) == 0)
        return cmp == len;
    }
    n--;
    (*cp)++;
  }

  return 0;
}