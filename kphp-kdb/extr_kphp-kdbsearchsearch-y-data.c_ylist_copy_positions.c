#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ylist_decoder_stack_entry {int num; struct list_int_entry* positions_head; } ;
struct ylist_decoder {int capacity; int* positions; TYPE_1__* H; } ;
struct list_int_entry {int value; struct list_int_entry* next; } ;
struct TYPE_2__ {int* positions1; } ;

/* Variables and functions */
 int decoder_positions_max_capacity ; 
 scalar_t__ unlikely (int) ; 
 int* zmalloc (int) ; 

__attribute__((used)) static void ylist_copy_positions (struct ylist_decoder *dec, struct ylist_decoder_stack_entry *data) {
  if (unlikely (dec->capacity < data->num + 1)) {
    int c = dec->capacity;
    while (c < data->num + 1) {
      c *= 2;
    }
    //zfree (dec->positions, 4 * dec->capacity);
    dec->H->positions1 = dec->positions = zmalloc (4 * c);
    dec->capacity = c;
    if (decoder_positions_max_capacity < c) {
      decoder_positions_max_capacity = c;
    }
  }
  dec->positions[0] = data->num;
  int k;
  struct list_int_entry *p;
  for (k = 0, p = data->positions_head; p != NULL; p = p->next) {
    dec->positions[++k] = p->value;
  }
}