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
struct TYPE_7__ {char* buf; int buflen; } ;
typedef  TYPE_1__ WSFrame ;
struct TYPE_8__ {int status; } ;
typedef  TYPE_2__ WSClient ;

/* Variables and functions */
 int WS_CLOSE ; 
 int /*<<< orphan*/  WS_CLOSE_UNEXPECTED ; 
 int read_socket (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  ws_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ws_read_header (WSClient * client, WSFrame * frm, int pos, int need)
{
  char *buf = frm->buf;
  int bytes = 0;

  /* read the first 2 bytes for basic frame info */
  if ((bytes = read_socket (client, buf + pos, need)) < 1) {
    if (client->status & WS_CLOSE)
      ws_error (client, WS_CLOSE_UNEXPECTED, "Unable to read header");
    return bytes;
  }
  frm->buflen += bytes;
  frm->buf[frm->buflen] = '\0'; /* null-terminate */

  return bytes;
}