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
struct TYPE_4__ {int date; } ;
typedef  TYPE_1__ message_t ;

/* Variables and functions */

__attribute__((used)) static inline int message_cmp2 (message_t *a, message_t *b) {
  int x = a->date - b->date;
  if (x) {
    return x;
  }
  return (a < b ? -1 : (a > b ? 1 : 0));
}