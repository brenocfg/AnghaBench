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
struct results_queue_entry {int dummy; } ;

/* Variables and functions */
 size_t RESULTS_QUEUE_SIZE ; 
 struct results_queue_entry* RQ ; 
 size_t rq_right ; 
 size_t rq_size ; 

struct results_queue_entry *results_queue_push (void) {
  if (rq_size >= RESULTS_QUEUE_SIZE) {
    return NULL;
  }
  struct results_queue_entry *R = &RQ[rq_right];
  if (++rq_right == RESULTS_QUEUE_SIZE) {
    rq_right = 0;
  }
  rq_size++;
  return R;
}