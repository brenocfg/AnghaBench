#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  colist; TYPE_2__* pipein; } ;
typedef  TYPE_1__ WSServer ;
struct TYPE_11__ {int hlen; char* hdr; int /*<<< orphan*/  fd; TYPE_3__* packet; } ;
typedef  TYPE_2__ WSPipeIn ;
struct TYPE_12__ {int size; char* data; int len; scalar_t__ type; } ;
typedef  TYPE_3__ WSPacket ;

/* Variables and functions */
 int HDR_SIZE ; 
 int /*<<< orphan*/  clear_fifo_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  unpack_uint32 (char*,scalar_t__*) ; 
 int validate_fifo_packet (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ws_broadcast_fifo ; 
 int /*<<< orphan*/  ws_openfifo_in (TYPE_2__*) ; 
 int ws_read_fifo (int /*<<< orphan*/ ,char*,int*,int,int) ; 
 int /*<<< orphan*/  ws_send_strict_fifo_to_client (TYPE_1__*,scalar_t__,TYPE_3__*) ; 
 void* xcalloc (scalar_t__,int) ; 

__attribute__((used)) static void
handle_strict_fifo (WSServer * server)
{
  WSPipeIn *pi = server->pipein;
  WSPacket **pa = &pi->packet;
  int bytes = 0, readh = 0, need = 0;

  char *ptr = NULL;
  uint32_t listener = 0, type = 0, size = 0;

  readh = pi->hlen;     /* read from header so far */
  need = HDR_SIZE - readh;      /* need to read */
  if (need > 0) {
    if ((bytes = ws_read_fifo (pi->fd, pi->hdr, &pi->hlen, readh, need)) < 0)
      return;
    if (bytes != need)
      return;
  }

  /* unpack size, and type */
  ptr = pi->hdr;
  ptr += unpack_uint32 (ptr, &listener);
  ptr += unpack_uint32 (ptr, &type);
  ptr += unpack_uint32 (ptr, &size);

  if (validate_fifo_packet (listener, type, size) == 1) {
    close (pi->fd);
    clear_fifo_packet (pi);
    ws_openfifo_in (pi);
    return;
  }

  if ((*pa) == NULL) {
    (*pa) = xcalloc (1, sizeof (WSPacket));
    (*pa)->type = type;
    (*pa)->size = size;
    (*pa)->data = xcalloc (size, sizeof (char));
  }

  readh = (*pa)->len;   /* read from payload so far */
  need = (*pa)->size - readh;   /* need to read */
  if (need > 0) {
    if ((bytes =
         ws_read_fifo (pi->fd, (*pa)->data, &(*pa)->len, readh, need)) < 0)
      return;
    if (bytes != need)
      return;
  }

  /* no clients to send data to */
  if (list_count (server->colist) == 0) {
    clear_fifo_packet (pi);
    return;
  }

  /* Either send it to a specific client or brodcast message to all
   * clients */
  if (listener != 0)
    ws_send_strict_fifo_to_client (server, listener, *pa);
  else
    list_foreach (server->colist, ws_broadcast_fifo, *pa);
  clear_fifo_packet (pi);
}