#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WSClient ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ GSLList ;

/* Variables and functions */
 TYPE_1__* list_find (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ws_find_client_sock_in_list ; 

__attribute__((used)) static WSClient *
ws_get_client_from_list (int listener, GSLList ** colist)
{
  GSLList *match = NULL;

  /* Find the client data for the socket in use */
  if (!(match = list_find (*colist, ws_find_client_sock_in_list, &listener)))
    return NULL;
  return (WSClient *) match->data;
}