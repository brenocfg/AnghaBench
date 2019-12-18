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
 int /*<<< orphan*/  advance_buff () ; 
 int /*<<< orphan*/  assert (int) ; 
 char* rend ; 
 char* rptr ; 

int read_int (void) {
  if (rptr == rend) {
    advance_buff ();
    assert (rptr != rend);
  }
  while ((*rptr < '0' || *rptr > '9') && *rptr != '-') {
    rptr ++;
    if (rptr == rend) {
      advance_buff ();
      assert (rptr != rend);
    }
  }
  if (rptr + 20 > rend) {
    advance_buff ();
  }
  int sign = 1;
  while (*rptr == '-') {
    sign = -sign;
    rptr ++;
  }
  int res = 0;
  while (rptr < rend && *rptr >= '0' && *rptr <= '9') {
    res = res * 10 + *rptr - '0';
    rptr ++;
  }
  if (sign < 0) {
    res = -res;
  }
  return res;
}