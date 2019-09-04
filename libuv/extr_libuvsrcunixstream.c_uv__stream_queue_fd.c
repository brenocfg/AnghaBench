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
struct TYPE_7__ {TYPE_2__* queued_fds; } ;
typedef  TYPE_1__ uv_stream_t ;
struct TYPE_8__ {unsigned int size; unsigned int offset; int* fds; } ;
typedef  TYPE_2__ uv__stream_queued_fds_t ;

/* Variables and functions */
 int UV_ENOMEM ; 
 TYPE_2__* uv__malloc (unsigned int) ; 
 TYPE_2__* uv__realloc (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static int uv__stream_queue_fd(uv_stream_t* stream, int fd) {
  uv__stream_queued_fds_t* queued_fds;
  unsigned int queue_size;

  queued_fds = stream->queued_fds;
  if (queued_fds == NULL) {
    queue_size = 8;
    queued_fds = uv__malloc((queue_size - 1) * sizeof(*queued_fds->fds) +
                            sizeof(*queued_fds));
    if (queued_fds == NULL)
      return UV_ENOMEM;
    queued_fds->size = queue_size;
    queued_fds->offset = 0;
    stream->queued_fds = queued_fds;

    /* Grow */
  } else if (queued_fds->size == queued_fds->offset) {
    queue_size = queued_fds->size + 8;
    queued_fds = uv__realloc(queued_fds,
                             (queue_size - 1) * sizeof(*queued_fds->fds) +
                              sizeof(*queued_fds));

    /*
     * Allocation failure, report back.
     * NOTE: if it is fatal - sockets will be closed in uv__stream_close
     */
    if (queued_fds == NULL)
      return UV_ENOMEM;
    queued_fds->size = queue_size;
    stream->queued_fds = queued_fds;
  }

  /* Put fd in a queue */
  queued_fds->fds[queued_fds->offset++] = fd;

  return 0;
}