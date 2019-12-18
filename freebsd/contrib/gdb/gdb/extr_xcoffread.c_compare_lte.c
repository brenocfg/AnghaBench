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
struct linetable_entry {int pc; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_lte (const void *lte1p, const void *lte2p)
{
  struct linetable_entry *lte1 = (struct linetable_entry *) lte1p;
  struct linetable_entry *lte2 = (struct linetable_entry *) lte2p;
  return lte1->pc - lte2->pc;
}