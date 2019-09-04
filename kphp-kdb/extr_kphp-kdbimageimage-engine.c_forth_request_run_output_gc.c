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
struct forth_request {scalar_t__ timeout; struct forth_request* next; } ;

/* Variables and functions */
 scalar_t__ all_results_memory ; 
 int /*<<< orphan*/  forth_request_unload_prog (struct forth_request*) ; 
 scalar_t__ max_all_results ; 
 scalar_t__ now ; 
 struct forth_request with_output_free_list ; 

__attribute__((used)) static void forth_request_run_output_gc (void) {
  struct forth_request *p, *w;
  for (p = with_output_free_list.next; p != &with_output_free_list; p = w) {
    if (now <= p->timeout) {
      break;
    }
    w = p->next;
    forth_request_unload_prog (p);
  }
  for (p = with_output_free_list.next; all_results_memory > max_all_results && p != &with_output_free_list; p = w) {
    w = p->next;
    forth_request_unload_prog (p);
  }
}