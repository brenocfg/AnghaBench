#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fid; float val; } ;
typedef  TYPE_1__ score ;

/* Variables and functions */

inline float cross_product (score *a, score *b) {
//  return 1.0;
  float res = 0.2;
  while (a->fid >= 0 && b->fid >= 0) {
    if (a->fid == b->fid) {
      res += a->val * b->val;
      a++;
      b++;
    } else {
      if (a->val < b->val) {
        a++;
      } else {
        b++;
      }
    }
  }
  return res;
}