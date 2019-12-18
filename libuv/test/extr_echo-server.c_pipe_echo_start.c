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
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  on_connection ; 
 int /*<<< orphan*/  pipeServer ; 
 int /*<<< orphan*/ * server ; 
 int /*<<< orphan*/  serverType ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_unlink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int uv_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_pipe_bind (int /*<<< orphan*/ *,char*) ; 
 int uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* uv_strerror (int) ; 

__attribute__((used)) static int pipe_echo_start(char* pipeName) {
  int r;

#ifndef _WIN32
  {
    uv_fs_t req;
    uv_fs_unlink(NULL, &req, pipeName, NULL);
    uv_fs_req_cleanup(&req);
  }
#endif

  server = (uv_handle_t*)&pipeServer;
  serverType = PIPE;

  r = uv_pipe_init(loop, &pipeServer, 0);
  if (r) {
    fprintf(stderr, "uv_pipe_init: %s\n", uv_strerror(r));
    return 1;
  }

  r = uv_pipe_bind(&pipeServer, pipeName);
  if (r) {
    fprintf(stderr, "uv_pipe_bind: %s\n", uv_strerror(r));
    return 1;
  }

  r = uv_listen((uv_stream_t*)&pipeServer, SOMAXCONN, on_connection);
  if (r) {
    fprintf(stderr, "uv_pipe_listen: %s\n", uv_strerror(r));
    return 1;
  }

  return 0;
}