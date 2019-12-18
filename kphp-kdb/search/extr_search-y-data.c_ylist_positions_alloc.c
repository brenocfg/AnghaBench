#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ylist_decoder_stack_entry {int num; TYPE_1__* positions_tail; TYPE_1__* positions_head; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ list_int_entry_t ;
struct TYPE_6__ {int num; TYPE_1__* head; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 TYPE_4__ list_int_free_blocks ; 
 int /*<<< orphan*/  ylist_positions_free (struct ylist_decoder_stack_entry*) ; 
 TYPE_1__* zmalloc (int) ; 
 TYPE_1__* ztmalloc (int) ; 

__attribute__((used)) static void ylist_positions_alloc (struct ylist_decoder_stack_entry *data, int num) {
  //fprintf (stderr, "%s: (num = %d)\n", __func__, num);
  if (data->num) {
    ylist_positions_free (data);
  }
  data->num = num;
  int i = 0;
  list_int_entry_t *p;
  if (likely (num <= list_int_free_blocks.num)) {
    //fprintf (stderr, "%d <= %d\n", num, list_int_free_blocks.num);
    p = data->positions_head = list_int_free_blocks.head;
    for (i = 1; i < num; i++) {
      p = p->next;
    }
    data->positions_tail = p;
    list_int_free_blocks.num -= num;
    list_int_free_blocks.head = p->next;
    p->next = NULL;
  } else {
    data->positions_head = data->positions_tail = zmalloc (sizeof (*p));
    data->positions_tail->next = NULL;
    for (i = 1; i < num; i++) {
      p = ztmalloc (sizeof (*p));
      p->next = NULL;
      data->positions_tail->next = p;
      data->positions_tail = p;
    }
  }
}