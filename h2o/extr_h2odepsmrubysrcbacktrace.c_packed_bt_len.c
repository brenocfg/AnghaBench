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
struct backtrace_location {int /*<<< orphan*/  method_id; int /*<<< orphan*/  lineno; int /*<<< orphan*/  filename; } ;

/* Variables and functions */

__attribute__((used)) static int
packed_bt_len(struct backtrace_location *bt, int n)
{
  int len = 0;
  int i;

  for (i=0; i<n; i++) {
    if (!bt[i].filename && !bt[i].lineno && !bt[i].method_id)
      continue;
    len++;
  }
  return len;
}