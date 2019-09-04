#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ terminated; } ;
struct TYPE_5__ {int /*<<< orphan*/  q; TYPE_1__ Out; } ;
typedef  TYPE_2__ write_thread_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  delete_write_thread_query (int /*<<< orphan*/ ) ; 

int write_thread_check_completion (write_thread_arg_t *A) {
  if (A->Out.terminated) {
    delete_write_thread_query (A->q);
    return 1;
  }
  return 0;
}