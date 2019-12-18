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
struct TYPE_4__ {long date; } ;
typedef  TYPE_1__ entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  date_adj ; 

__attribute__((used)) static inline void fix_date (long a, entry_t *B, entry_t *C) {
  long min = a, max = C->date;
  if (min > max) { min = max; max = a; }
  if (B->date < min) { B->date = min; date_adj++; }
  else if (B->date > max) { B->date = max; date_adj++; }
}