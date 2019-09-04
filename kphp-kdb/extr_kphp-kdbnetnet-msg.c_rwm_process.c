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
struct raw_message {int total_bytes; int first_offset; int last_offset; struct msg_part* last; struct msg_part* first; } ;
struct msg_part {int offset; int len; struct msg_part* next; TYPE_1__* part; } ;
struct TYPE_2__ {void const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int rwm_process (struct raw_message *raw, int bytes, void (*process_block)(void *extra, const void *data, int len), void *extra) {
  assert (bytes >= 0);
  if (bytes > raw->total_bytes) {
    bytes = raw->total_bytes;    
  }
  if (!bytes) { return 0; }
  int x = bytes;
  if (raw->first) {
    struct msg_part *mp = raw->first;
    while (mp) {
      int start = (mp == raw->first) ? raw->first_offset : mp->offset;
      int len = (mp == raw->last) ? raw->last_offset - start: mp->len + mp->offset - start;
      if (len >= bytes) {
        process_block (extra, mp->part->data + start, bytes);
        bytes = 0;
        break;
      } 
      process_block (extra, mp->part->data + start, len);
      bytes -= len;
      mp = mp->next;
    }
    assert (!bytes);
  }
  return x;
}