#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t NUM_WRITES ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 scalar_t__ XFER_SIZE ; 
 int /*<<< orphan*/  alloc_cb ; 
 scalar_t__ bytes_read ; 
 scalar_t__ bytes_written ; 
 int /*<<< orphan*/  do_write (TYPE_1__*) ; 
 int /*<<< orphan*/  read_cb ; 
 int uv_read_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_writes_and_reads(uv_stream_t* handle) {
  size_t i;
  int r;

  bytes_written = 0;
  bytes_read = 0;

  for (i = 0; i < NUM_WRITES; i++) {
    do_write(handle);
  }

  r = uv_read_start(handle, alloc_cb, read_cb);
  ASSERT(r == 0);

  r = uv_run(handle->loop, UV_RUN_DEFAULT);
  ASSERT(r == 0);

  ASSERT(bytes_written == XFER_SIZE);
  ASSERT(bytes_read == XFER_SIZE);
}