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
typedef  int /*<<< orphan*/  WSClient ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EPIPE ; 
 scalar_t__ EWOULDBLOCK ; 
 int WS_CLOSE ; 
 int WS_ERR ; 
 scalar_t__ errno ; 
 int send_buffer (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ws_queue_sockbuf (int /*<<< orphan*/ *,char const*,int,int) ; 
 int ws_set_status (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
ws_respond_data (WSClient * client, const char *buffer, int len)
{
  int bytes = 0;

  bytes = send_buffer (client, buffer, len);
  if (bytes == -1 && errno == EPIPE)
    return ws_set_status (client, WS_ERR | WS_CLOSE, bytes);

  /* did not send all of it... buffer it for a later attempt */
  if (bytes < len || (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)))
    ws_queue_sockbuf (client, buffer, len, bytes);

  return bytes;
}