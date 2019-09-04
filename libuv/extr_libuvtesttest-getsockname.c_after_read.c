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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_shutdown_t ;
struct TYPE_3__ {scalar_t__ base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  after_shutdown ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ malloc (int) ; 
 int uv_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void after_read(uv_stream_t* handle,
                       ssize_t nread,
                       const uv_buf_t* buf) {
  uv_shutdown_t* req;
  int r;

  if (buf->base) {
    free(buf->base);
  }

  req = (uv_shutdown_t*) malloc(sizeof *req);
  r = uv_shutdown(req, handle, after_shutdown);
  ASSERT(r == 0);
}