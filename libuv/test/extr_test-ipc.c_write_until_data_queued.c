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
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_2__ {scalar_t__ write_queue_size; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__ channel ; 
 int /*<<< orphan*/  closed_handle_large_write_cb ; 
 int /*<<< orphan*/  large_buf ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * write_reqs ; 

__attribute__((used)) static unsigned int write_until_data_queued() {
  unsigned int i;
  int r;

  i = 0;
  do {
    r = uv_write(&write_reqs[i],
                 (uv_stream_t*)&channel,
                 &large_buf,
                 1,
                 closed_handle_large_write_cb);
    ASSERT(r == 0);
    i++;
  } while (channel.write_queue_size == 0 &&
           i < ARRAY_SIZE(write_reqs));

  return channel.write_queue_size;
}