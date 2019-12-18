#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int status; int /*<<< orphan*/ * sockqueue; } ;
typedef  TYPE_1__ WSClient ;

/* Variables and functions */
 int WS_THROTTLING ; 
 int ws_realloc_send_buf (TYPE_1__*,char const*,int) ; 
 int ws_respond_cache (TYPE_1__*) ; 
 int ws_respond_data (TYPE_1__*,char const*,int) ; 

__attribute__((used)) static int
ws_respond (WSClient * client, const char *buffer, int len)
{
  int bytes = 0;

  /* attempt to send the whole buffer buffer */
  if (client->sockqueue == NULL)
    bytes = ws_respond_data (client, buffer, len);
  /* buffer not empty, just append new data iff we're not throttling the
   * client */
  else if (client->sockqueue != NULL && buffer != NULL &&
           !(client->status & WS_THROTTLING)) {
    if (ws_realloc_send_buf (client, buffer, len) == 1)
      return bytes;
  }
  /* send from cache buffer */
  else {
    bytes = ws_respond_cache (client);
  }

  return bytes;
}