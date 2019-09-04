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
struct statsx_gather_extra {int valid_until; int /*<<< orphan*/ * subcnt; } ;

/* Variables and functions */
 int MAX_SUBCOUNTER ; 
 scalar_t__ is_null (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int *serialize_subcnt_list_raw (int *ptr, struct statsx_gather_extra *C) {
  /* 
     don't output broken stats (dirty hack)
     php: mktime (12, 0, 0, 2, 2, 2011) == 1296637200
          Feb 02 2011, 12:00
  */
  if (C->valid_until < 1296637200) {
    *(ptr++)  = 0;
    return ptr;
  }
  if (is_null (C->subcnt, MAX_SUBCOUNTER)) {
    *(ptr++)  = 0;
    return ptr;
  }
  *(ptr++) = MAX_SUBCOUNTER;
  int i;
  for (i = 0; i < MAX_SUBCOUNTER; i++) {
    *(ptr++) = C->subcnt[i];
  }
  return ptr;
}