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
struct TYPE_5__ {int /*<<< orphan*/  colist; } ;
typedef  TYPE_1__ WSServer ;
struct TYPE_6__ {scalar_t__ headers; int /*<<< orphan*/  listener; } ;
typedef  TYPE_2__ WSClient ;
typedef  int /*<<< orphan*/  GSLList ;

/* Variables and functions */
 int /*<<< orphan*/  list_remove_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_clear_handshake_headers (scalar_t__) ; 
 int /*<<< orphan*/ * ws_get_list_node_from_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ws_remove_client_from_list (WSClient * client, WSServer * server)
{
  GSLList *node = NULL;

  if (!(node = ws_get_list_node_from_list (client->listener, &server->colist)))
    return;

  if (client->headers)
    ws_clear_handshake_headers (client->headers);
  list_remove_node (&server->colist, node);
}