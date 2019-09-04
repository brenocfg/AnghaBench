#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ WSPacket ;
struct TYPE_7__ {TYPE_1__* headers; } ;
typedef  TYPE_3__ WSClient ;
struct TYPE_5__ {int /*<<< orphan*/ * ws_accept; } ;

/* Variables and functions */
 int /*<<< orphan*/  ws_send_data (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ws_broadcast_fifo (void *value, void *user_data)
{
  WSClient *client = value;
  WSPacket *packet = user_data;

  if (client == NULL || user_data == NULL)
    return 1;
  /* no handshake for this client */
  if (client->headers == NULL || client->headers->ws_accept == NULL)
    return 1;

  ws_send_data (client, packet->type, packet->data, packet->size);

  return 0;
}