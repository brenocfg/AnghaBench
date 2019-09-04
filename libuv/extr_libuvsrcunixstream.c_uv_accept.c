#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_udp_t ;
struct TYPE_7__ {scalar_t__ loop; int accepted_fd; int type; int /*<<< orphan*/  io_watcher; TYPE_2__* queued_fds; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ uv_stream_t ;
struct TYPE_8__ {int* fds; scalar_t__ offset; } ;
typedef  TYPE_2__ uv__stream_queued_fds_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int UV_EAGAIN ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  UV_HANDLE_BOUND ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_WRITABLE ; 
#define  UV_NAMED_PIPE 130 
#define  UV_TCP 129 
#define  UV_UDP 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int /*<<< orphan*/  uv__free (TYPE_2__*) ; 
 int /*<<< orphan*/  uv__io_start (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv__stream_open (TYPE_1__*,int,int) ; 
 int uv_udp_open (int /*<<< orphan*/ *,int) ; 

int uv_accept(uv_stream_t* server, uv_stream_t* client) {
  int err;

  assert(server->loop == client->loop);

  if (server->accepted_fd == -1)
    return UV_EAGAIN;

  switch (client->type) {
    case UV_NAMED_PIPE:
    case UV_TCP:
      err = uv__stream_open(client,
                            server->accepted_fd,
                            UV_HANDLE_READABLE | UV_HANDLE_WRITABLE);
      if (err) {
        /* TODO handle error */
        uv__close(server->accepted_fd);
        goto done;
      }
      break;

    case UV_UDP:
      err = uv_udp_open((uv_udp_t*) client, server->accepted_fd);
      if (err) {
        uv__close(server->accepted_fd);
        goto done;
      }
      break;

    default:
      return UV_EINVAL;
  }

  client->flags |= UV_HANDLE_BOUND;

done:
  /* Process queued fds */
  if (server->queued_fds != NULL) {
    uv__stream_queued_fds_t* queued_fds;

    queued_fds = server->queued_fds;

    /* Read first */
    server->accepted_fd = queued_fds->fds[0];

    /* All read, free */
    assert(queued_fds->offset > 0);
    if (--queued_fds->offset == 0) {
      uv__free(queued_fds);
      server->queued_fds = NULL;
    } else {
      /* Shift rest */
      memmove(queued_fds->fds,
              queued_fds->fds + 1,
              queued_fds->offset * sizeof(*queued_fds->fds));
    }
  } else {
    server->accepted_fd = -1;
    if (err == 0)
      uv__io_start(server->loop, &server->io_watcher, POLLIN);
  }
  return err;
}