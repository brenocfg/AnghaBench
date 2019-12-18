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
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_3__ {char* base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_EOF ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read1_cb(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
  int i;
  ASSERT(tcp != NULL);

  if (nread >= 0) {
    for (i = 0; i < nread; ++i)
      ASSERT(buf->base[i] == 'P');
  } else {
    ASSERT(nread == UV_EOF);
    printf("GOT EOF\n");
    uv_close((uv_handle_t*)tcp, close_cb);
  }
}