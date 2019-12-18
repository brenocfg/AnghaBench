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
struct raw_message {scalar_t__ magic; int total_bytes; int last_offset; int first_offset; struct msg_part* last; struct msg_part* first; } ;
struct msg_part {int offset; int len; struct msg_part* next; } ;

/* Variables and functions */
 scalar_t__ RM_INIT_MAGIC ; 
 scalar_t__ RM_TMP_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 

int rwm_check (struct raw_message *raw) {
  assert (raw->magic == RM_INIT_MAGIC || raw->magic == RM_TMP_MAGIC);
  if (!raw->first) { 
    assert (!raw->total_bytes);
  } else {
    int total_size  = 0;
    struct msg_part *mp = raw->first;
    while (mp != 0) {
      int size = (mp == raw->last ? raw->last_offset : mp->offset + mp->len) - (mp == raw->first ? raw->first_offset : mp->offset);
      total_size += size;
      if (mp == raw->last) { break; }
      mp = mp->next;
    }
    assert (mp == raw->last);
    assert (total_size == raw->total_bytes);
  }
  return 0;
}