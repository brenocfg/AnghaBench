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
struct rpc_buffer {void* eptr; void* wptr; void* sptr; void* rptr; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_BUFFER_MAGIC ; 
 struct rpc_buffer* zzmalloc (int) ; 

__attribute__((used)) static inline struct rpc_buffer *buffer_create_data (void *data, int len) {
  struct rpc_buffer *buf = zzmalloc (sizeof (struct rpc_buffer));
  buf->magic = RPC_BUFFER_MAGIC;
  buf->rptr = buf->sptr = data;
  buf->wptr = buf->eptr = data + len;
  return buf;
}