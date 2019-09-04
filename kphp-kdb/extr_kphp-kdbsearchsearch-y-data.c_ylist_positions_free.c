#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ylist_decoder_stack_entry {scalar_t__ num; TYPE_1__* positions_tail; int /*<<< orphan*/  positions_head; } ;
struct TYPE_4__ {scalar_t__ num; TYPE_1__* tail; int /*<<< orphan*/  head; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 TYPE_2__ list_int_free_blocks ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ylist_positions_free (struct ylist_decoder_stack_entry *data) {
  if (unlikely (!list_int_free_blocks.num)) {
    list_int_free_blocks.head = data->positions_head;
  } else {
    list_int_free_blocks.tail->next = data->positions_head;
  }
  list_int_free_blocks.tail = data->positions_tail;
  list_int_free_blocks.num += data->num;
}