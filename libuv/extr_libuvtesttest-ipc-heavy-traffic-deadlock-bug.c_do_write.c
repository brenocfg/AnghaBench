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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct write_info {int /*<<< orphan*/  write_req; int /*<<< orphan*/ * buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BUFFERS_PER_WRITE ; 
 int /*<<< orphan*/  BUFFER_CONTENT ; 
 int /*<<< orphan*/  BUFFER_SIZE ; 
 struct write_info* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_buf_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb ; 

__attribute__((used)) static void do_write(uv_stream_t* handle) {
  struct write_info* write_info;
  uv_buf_t bufs[BUFFERS_PER_WRITE];
  size_t i;
  int r;

  write_info = malloc(sizeof *write_info);
  ASSERT(write_info != NULL);

  for (i = 0; i < BUFFERS_PER_WRITE; i++) {
    memset(&write_info->buffers[i], BUFFER_CONTENT, BUFFER_SIZE);
    bufs[i] = uv_buf_init(write_info->buffers[i], BUFFER_SIZE);
  }

  r = uv_write(
      &write_info->write_req, handle, bufs, BUFFERS_PER_WRITE, write_cb);
  ASSERT(r == 0);
}