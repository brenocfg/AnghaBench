#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_5__ {int type; int size; char* data; int len; } ;
typedef  TYPE_1__ WSPacket ;
struct TYPE_6__ {int fd; int* self_pipe; int hlen; char* hdr; TYPE_1__* packet; } ;
typedef  TYPE_2__ GWSReader ;

/* Variables and functions */
#define  EINTR 128 
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int HDR_SIZE ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  clear_fifo_packet (TYPE_2__*) ; 
 int errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 
 void stub1 (int) ; 
 int /*<<< orphan*/  unpack_uint32 (char*,int*) ; 
 int ws_read_fifo (int,char*,int*,int,int) ; 
 void* xcalloc (int,int) ; 

int
read_fifo (GWSReader * gwsreader, fd_set rfds, fd_set wfds, void (*f) (int))
{
  WSPacket **pa = &gwsreader->packet;
  char *ptr;
  int bytes = 0, readh = 0, need = 0, fd = gwsreader->fd, max = 0;
  uint32_t listener = 0, type = 0, size = 0;

  FD_ZERO (&rfds);
  FD_ZERO (&wfds);
  /* self-pipe trick to stop the event loop */
  FD_SET (gwsreader->self_pipe[0], &rfds);
  /* fifo */
  FD_SET (fd, &rfds);
  max = MAX (fd, gwsreader->self_pipe[0]);

  if (select (max + 1, &rfds, &wfds, NULL, NULL) == -1) {
    switch (errno) {
    case EINTR:
      break;
    default:
      FATAL ("Unable to select: %s.", strerror (errno));
    }
  }
  /* handle self-pipe trick */
  if (FD_ISSET (gwsreader->self_pipe[0], &rfds))
    return 1;
  if (!FD_ISSET (fd, &rfds)) {
    LOG (("No file descriptor set on read_message()\n"));
    return 0;
  }

  readh = gwsreader->hlen;      /* read from header so far */
  need = HDR_SIZE - readh;      /* need to read */
  if (need > 0) {
    if ((bytes =
         ws_read_fifo (fd, gwsreader->hdr, &gwsreader->hlen, readh, need)) < 0)
      return 0;
    if (bytes != need)
      return 0;
  }

  /* unpack size, and type */
  ptr = gwsreader->hdr;
  ptr += unpack_uint32 (ptr, &listener);
  ptr += unpack_uint32 (ptr, &type);
  ptr += unpack_uint32 (ptr, &size);

  if ((*pa) == NULL) {
    (*pa) = xcalloc (1, sizeof (WSPacket));
    (*pa)->type = type;
    (*pa)->size = size;
    (*pa)->data = xcalloc (size, sizeof (char));
  }

  readh = (*pa)->len;   /* read from payload so far */
  need = (*pa)->size - readh;   /* need to read */
  if (need > 0) {
    if ((bytes = ws_read_fifo (fd, (*pa)->data, &(*pa)->len, readh, need)) < 0)
      return 0;
    if (bytes != need)
      return 0;
  }
  clear_fifo_packet (gwsreader);
  /* fast forward JSON data to the given client */
  (*f) (listener);

  return 0;
}