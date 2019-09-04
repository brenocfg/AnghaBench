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

/* Variables and functions */
 long MSG_BUFFERS_CHUNK_SIZE ; 
 long MSG_DEFAULT_MAX_ALLOCATED_BYTES ; 
 long MSG_MAX_ALLOCATED_BYTES ; 
 long allocated_buffer_chunks ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_size_values ; 
 int /*<<< orphan*/  init_buffer_chunk_headers () ; 
 long max_allocated_buffer_bytes ; 
 unsigned long max_buffer_chunks ; 

int init_msg_buffers (long max_buffer_bytes) {
  if (!max_buffer_bytes) {
    max_buffer_bytes = max_allocated_buffer_bytes ?: MSG_DEFAULT_MAX_ALLOCATED_BYTES;
  }

  assert (max_buffer_bytes >= 0 && max_buffer_bytes <= MSG_MAX_ALLOCATED_BYTES);
  assert (max_buffer_bytes >= allocated_buffer_chunks * MSG_BUFFERS_CHUNK_SIZE);

  max_allocated_buffer_bytes = max_buffer_bytes;
  max_buffer_chunks = (unsigned long) max_buffer_bytes / MSG_BUFFERS_CHUNK_SIZE;

  if (!buffer_size_values) {
    init_buffer_chunk_headers ();
  }

  return 1;
}