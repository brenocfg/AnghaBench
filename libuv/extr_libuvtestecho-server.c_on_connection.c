#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_7__ {struct TYPE_7__* data; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_pipe_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  PIPE 129 
#define  TCP 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  after_read ; 
 int /*<<< orphan*/  echo_alloc ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  loop ; 
 TYPE_1__* malloc (int) ; 
 int serverType ; 
 int /*<<< orphan*/  stderr ; 
 int uv_accept (TYPE_1__*,TYPE_1__*) ; 
 char* uv_err_name (int) ; 
 int uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_read_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_connection(uv_stream_t* server, int status) {
  uv_stream_t* stream;
  int r;

  if (status != 0) {
    fprintf(stderr, "Connect error %s\n", uv_err_name(status));
  }
  ASSERT(status == 0);

  switch (serverType) {
  case TCP:
    stream = malloc(sizeof(uv_tcp_t));
    ASSERT(stream != NULL);
    r = uv_tcp_init(loop, (uv_tcp_t*)stream);
    ASSERT(r == 0);
    break;

  case PIPE:
    stream = malloc(sizeof(uv_pipe_t));
    ASSERT(stream != NULL);
    r = uv_pipe_init(loop, (uv_pipe_t*)stream, 0);
    ASSERT(r == 0);
    break;

  default:
    ASSERT(0 && "Bad serverType");
    abort();
  }

  /* associate server with stream */
  stream->data = server;

  r = uv_accept(server, stream);
  ASSERT(r == 0);

  r = uv_read_start(stream, echo_alloc, after_read);
  ASSERT(r == 0);
}