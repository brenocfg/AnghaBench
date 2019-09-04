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
typedef  int /*<<< orphan*/  uv_req_t ;
typedef  int /*<<< orphan*/  uv_connect_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TARGET_CONNECTIONS ; 
 scalar_t__ TCP ; 
 int /*<<< orphan*/  do_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  maybe_connect_some () ; 
 int /*<<< orphan*/ * pipe_write_handles ; 
 int /*<<< orphan*/  req_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_stats_collection () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * tcp_write_handles ; 
 scalar_t__ type ; 
 char* uv_strerror (int) ; 
 int write_sockets ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  int i;

  if (status) {
    fprintf(stderr, "%s", uv_strerror(status));
    fflush(stderr);
  }
  ASSERT(status == 0);

  write_sockets++;
  req_free((uv_req_t*) req);

  maybe_connect_some();

  if (write_sockets == TARGET_CONNECTIONS) {
    start_stats_collection();

    /* Yay! start writing */
    for (i = 0; i < write_sockets; i++) {
      if (type == TCP)
        do_write((uv_stream_t*) &tcp_write_handles[i]);
      else
        do_write((uv_stream_t*) &pipe_write_handles[i]);
    }
  }
}