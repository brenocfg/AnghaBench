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
struct msg_buffers_chunk {scalar_t__ magic; int (* free_buffer ) (struct msg_buffers_chunk*,struct msg_buffer*) ;} ;
struct msg_buffer {struct msg_buffers_chunk* chunk; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ MSG_CHUNK_USED_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (struct msg_buffers_chunk*,struct msg_buffer*) ; 

int free_msg_buffer (struct msg_buffer *X) {
  assert (!X->refcnt);
  struct msg_buffers_chunk *C = X->chunk;
  assert (C->magic == MSG_CHUNK_USED_MAGIC);
  return C->free_buffer (C, X);
}