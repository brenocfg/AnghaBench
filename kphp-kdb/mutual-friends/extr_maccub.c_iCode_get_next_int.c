#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pred; int* ptr; } ;
typedef  TYPE_1__ iCode_iterator ;

/* Variables and functions */

int iCode_get_next_int (iCode_iterator *it, int r) {
  int k = 0, p = 1, res;

  if (r == 1) {
    return 0;
  }

  while (p < r) {
    p += p;
    k++;
  }

  if (it->pred + k <= 8) {
    res = ( ( *it->ptr ) >> it->pred ) & ( (1 << k) - 1 );
    it->pred += k;
    return res;
  }

  res = ( ( *it->ptr++ ) >> it->pred );
  it->pred = k - (8 - it->pred);

  while (it->pred > 8) {
    res = (res << 8) + *it->ptr++;
    it->pred -= 8;
  }

  res = (res << it->pred) + ( *it->ptr & ( (1 << it->pred) - 1) );
  return res;

}