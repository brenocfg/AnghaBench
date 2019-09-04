#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WSServer ;
struct TYPE_7__ {TYPE_1__* headers; } ;
typedef  TYPE_2__ WSClient ;
struct TYPE_6__ {scalar_t__ reading; } ;

/* Variables and functions */
 int ws_get_handshake (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ws_get_message (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
read_client_data (WSClient * client, WSServer * server)
{
  int bytes = 0;

  /* Handshake */
  if ((!(client->headers) || (client->headers->reading)))
    bytes = ws_get_handshake (client, server);
  /* Message */
  else
    bytes = ws_get_message (client, server);

  return bytes;
}