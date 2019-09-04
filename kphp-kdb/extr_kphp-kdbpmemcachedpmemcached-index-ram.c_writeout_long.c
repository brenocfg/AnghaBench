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
 int BUFFSIZE ; 
 int Buff ; 
 int /*<<< orphan*/  flushout () ; 
 scalar_t__ unlikely (int) ; 
 int wptr ; 

__attribute__((used)) static inline void writeout_long (long long value) {
  if (unlikely (wptr > Buff + BUFFSIZE - 8)) {
    flushout();
  }
  *((long long *) wptr) = value;
  wptr += 8;
}