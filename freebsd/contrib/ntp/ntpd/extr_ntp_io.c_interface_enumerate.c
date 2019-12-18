#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* interface_receiver_t ) (void*,TYPE_1__*) ;
struct TYPE_6__ {TYPE_5__* ep; int /*<<< orphan*/  action; } ;
typedef  TYPE_1__ interface_info_t ;
struct TYPE_7__ {struct TYPE_7__* elink; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFS_EXISTS ; 
 TYPE_5__* ep_list ; 
 int /*<<< orphan*/  stub1 (void*,TYPE_1__*) ; 

void
interface_enumerate(
	interface_receiver_t	receiver,
	void *			data
	)
{
	interface_info_t ifi;

	ifi.action = IFS_EXISTS;
	for (ifi.ep = ep_list; ifi.ep != NULL; ifi.ep = ifi.ep->elink)
		(*receiver)(data, &ifi);
}