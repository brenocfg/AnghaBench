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
struct raw_message {scalar_t__ total_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct raw_message*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ out_buf_bytes ; 
 scalar_t__ out_buf_first_int ; 
 int out_buf_init ; 
 struct raw_message out_buf_msg ; 
 int out_buf_packets ; 
 scalar_t__ out_buf_size ; 
 int out_buf_start ; 
 int /*<<< orphan*/  rwm_push_data (struct raw_message*,int*,int) ; 
 int /*<<< orphan*/  rwm_union (struct raw_message*,struct raw_message*) ; 

void __out_buf_add (struct raw_message *raw, int num) {
  out_buf_bytes += raw->total_bytes;
  if (!out_buf_init) {
    out_buf_msg = *raw;
    //rwm_clone (&out_buf_msg, raw);
    out_buf_first_int = raw->total_bytes;
    out_buf_packets = 1; 
    out_buf_size = raw->total_bytes;
    out_buf_start = num;
    out_buf_init = 1;
    memset (raw, 0, sizeof (*raw));
  } else {
//    struct raw_message t;
//    rwm_clone (&t, raw);
    int x = raw->total_bytes;
    rwm_push_data (&out_buf_msg, &x, 4);
    rwm_union (&out_buf_msg, raw);

    out_buf_packets ++;
    out_buf_size += x + 4;
    assert ((out_buf_size) == out_buf_msg.total_bytes);
  }
}