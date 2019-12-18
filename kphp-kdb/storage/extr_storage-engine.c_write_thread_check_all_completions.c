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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ write_thread_arg_t ;

/* Variables and functions */
 TYPE_1__* active_write_threads ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 
 scalar_t__ write_thread_check_completion (TYPE_1__*) ; 

int write_thread_check_all_completions (void) {
  int sum = 0;
  write_thread_arg_t *p = active_write_threads;
  while (p != NULL) {
    write_thread_arg_t *n = p->next;
    sum += write_thread_check_completion (p);
    p = n;
  }
  if (sum) {
    vkprintf (2, "write_thread_check_all_completion returns %d.\n", sum);
  }
  return sum;
}