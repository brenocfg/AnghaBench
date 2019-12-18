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
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ UV_EOF ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  closed_handle_data_read ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* uv_strerror (scalar_t__) ; 

__attribute__((used)) static void on_read_closed_handle(uv_stream_t* handle,
                                  ssize_t nread,
                                  const uv_buf_t* buf) {
  if (nread == 0 || nread == UV_EOF) {
    free(buf->base);
    return;
  }

  if (nread < 0) {
    printf("error recving on channel: %s\n", uv_strerror(nread));
    abort();
  }

  closed_handle_data_read += nread;
  free(buf->base);
}