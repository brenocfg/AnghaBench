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
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int i; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ UV_ECONNRESET ; 
 scalar_t__ UV_EOF ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  conns_failed ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* p ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* uv_err_name (scalar_t__) ; 

__attribute__((used)) static void read_cb(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {

  ASSERT(stream != NULL);

#if DEBUG
  printf("read_cb %d\n", p->i);
#endif

  uv_close((uv_handle_t*)stream, close_cb);

  if (nread < 0) {
    if (nread == UV_EOF) {
      ;
    } else if (nread == UV_ECONNRESET) {
      conns_failed++;
    } else {
      fprintf(stderr, "read error %s\n", uv_err_name(nread));
      ASSERT(0);
    }
  }
}