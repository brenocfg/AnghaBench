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
struct port_info {int /*<<< orphan*/  link_check_task; int /*<<< orphan*/  port_id; struct adapter* adapter; } ;
struct adapter {int /*<<< orphan*/  tq; int /*<<< orphan*/  open_device_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
link_check_callout(void *arg)
{
	struct port_info *pi = arg;
	struct adapter *sc = pi->adapter;

	if (!isset(&sc->open_device_map, pi->port_id))
		return;

	taskqueue_enqueue(sc->tq, &pi->link_check_task);
}