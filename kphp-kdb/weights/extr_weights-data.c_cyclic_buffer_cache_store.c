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
struct TYPE_3__ {int vector_id; int timestamp; int coord_id; } ;
typedef  TYPE_1__ weights_cyclic_buffer_en_t ;

/* Variables and functions */
 TYPE_1__* CC ; 
 unsigned int WEIGHTS_CB_CACHE_SIZE ; 

__attribute__((used)) static int cyclic_buffer_cache_store (int vector_id, int coord_id, int timestamp) {
  unsigned int h = (vector_id * 63617 + coord_id) * 63617 + timestamp;
  h %= WEIGHTS_CB_CACHE_SIZE;
  weights_cyclic_buffer_en_t *C = CC + h;
  if (C->vector_id == vector_id && C->timestamp == timestamp && C->coord_id == coord_id) {
    return 0;
  }
  C->vector_id = vector_id;
  C->coord_id = coord_id;
  C->timestamp = timestamp;
  return 1;
}