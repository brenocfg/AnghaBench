#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  listener; } ;
typedef  TYPE_1__ WSClient ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int WS_CLOSE ; 
 int WS_ERR ; 
 int WS_READING ; 
 scalar_t__ errno ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int ws_set_status (TYPE_1__*,int,int) ; 

__attribute__((used)) static int
read_plain_socket (WSClient * client, char *buffer, int size)
{
  int bytes = 0;

  bytes = recv (client->listener, buffer, size, 0);

  if (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
    return ws_set_status (client, WS_READING, bytes);
  else if (bytes == -1 || bytes == 0)
    return ws_set_status (client, WS_ERR | WS_CLOSE, bytes);

  return bytes;
}