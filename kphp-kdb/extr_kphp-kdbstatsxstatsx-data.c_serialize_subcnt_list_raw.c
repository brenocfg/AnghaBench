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
struct counter {int valid_until; unsigned long long mask_subcnt; int /*<<< orphan*/ * subcnt; } ;

/* Variables and functions */

__attribute__((used)) static int *serialize_subcnt_list_raw (int *ptr, struct counter *C) {
  /* 
     don't output broken stats (dirty hack)
     php: mktime (12, 0, 0, 2, 2, 2011) == 1296637200
          Feb 02 2011, 12:00
  */
  if (C->valid_until < 1296637200) {
    *(ptr++)  = 0;
    return ptr;
  }
  if (!C->subcnt) {
    *(ptr++) = 0;
    return ptr;
  }
  *(ptr++) = 64;
  unsigned long long u = 1;
  int i, j;
  for (i = 0, j = 0; i < 64; i++, u <<= 1) 
    if (u & C->mask_subcnt) {
      *(ptr++) = C->subcnt[j++];
    } else {
      *(ptr++) = 0;
    }
  return ptr;
}