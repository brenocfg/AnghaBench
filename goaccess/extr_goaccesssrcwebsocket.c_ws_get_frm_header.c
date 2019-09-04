#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int buflen; scalar_t__ payloadlen; int payload_offset; scalar_t__ reading; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ WSFrame ;
struct TYPE_14__ {TYPE_1__* frame; } ;
typedef  TYPE_2__ WSClient ;
struct TYPE_15__ {scalar_t__ max_frm_size; } ;

/* Variables and functions */
 int WS_CLOSE ; 
 int /*<<< orphan*/  WS_CLOSE_TOO_LARGE ; 
 int WS_ERR ; 
 int WS_OK ; 
 int WS_READING ; 
 TYPE_1__* new_wsframe () ; 
 int /*<<< orphan*/  ws_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int ws_read_header (TYPE_2__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ws_set_extended_header_size (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ws_set_front_header_fields (TYPE_2__*) ; 
 int /*<<< orphan*/  ws_set_masking_key (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws_set_payloadlen (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ws_set_status (TYPE_2__*,int,int) ; 
 TYPE_3__ wsconfig ; 

__attribute__((used)) static int
ws_get_frm_header (WSClient * client)
{
  WSFrame **frm = NULL;
  int bytes = 0, readh = 0, need = 0, offset = 0, extended = 0;

  if (client->frame == NULL)
    client->frame = new_wsframe ();

  frm = &client->frame;

  /* Read the first 2 bytes for basic frame info */
  readh = (*frm)->buflen;       /* read from header so far */
  need = 2 - readh;     /* need to read */
  if (need > 0) {
    if ((bytes = ws_read_header (client, (*frm), readh, need)) < 1)
      return bytes;
    if (bytes != need)
      return ws_set_status (client, WS_READING, bytes);
  }
  offset += 2;

  if (ws_set_front_header_fields (client) != 0)
    return bytes;

  ws_set_extended_header_size ((*frm)->buf, &extended);
  /* read the extended header */
  readh = (*frm)->buflen;       /* read from header so far */
  need = (extended + offset) - readh;   /* read from header field so far */
  if (need > 0) {
    if ((bytes = ws_read_header (client, (*frm), readh, need)) < 1)
      return bytes;
    if (bytes != need)
      return ws_set_status (client, WS_READING, bytes);
  }
  offset += extended;

  /* read the masking key */
  readh = (*frm)->buflen;       /* read from header so far */
  need = (4 + offset) - readh;
  if (need > 0) {
    if ((bytes = ws_read_header (client, (*frm), readh, need)) < 1)
      return bytes;
    if (bytes != need)
      return ws_set_status (client, WS_READING, bytes);
  }
  offset += 4;

  ws_set_payloadlen ((*frm), (*frm)->buf);
  ws_set_masking_key ((*frm), (*frm)->buf);

  if ((*frm)->payloadlen > wsconfig.max_frm_size) {
    ws_error (client, WS_CLOSE_TOO_LARGE, "Frame is too big");
    return ws_set_status (client, WS_ERR | WS_CLOSE, bytes);
  }

  (*frm)->buflen = 0;
  (*frm)->reading = 0;
  (*frm)->payload_offset = offset;

  return ws_set_status (client, WS_OK, bytes);
}