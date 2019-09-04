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
struct TYPE_3__ {int /*<<< orphan*/  last_fail_time; scalar_t__ sequential_fails; int /*<<< orphan*/  fails; int /*<<< orphan*/  success; } ;
typedef  TYPE_1__ stat_read_t ;

/* Variables and functions */
 int /*<<< orphan*/  now ; 

void update_read_stat (stat_read_t *S, int success) {
  if (success) {
    S->success++;
    S->sequential_fails = 0;
  } else {
    S->fails++;
    S->sequential_fails++;
    S->last_fail_time = now;
  }
}