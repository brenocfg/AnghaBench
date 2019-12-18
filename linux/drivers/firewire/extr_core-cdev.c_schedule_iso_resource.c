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
struct iso_resource {int /*<<< orphan*/  client; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  client_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_workqueue ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void schedule_iso_resource(struct iso_resource *r, unsigned long delay)
{
	client_get(r->client);
	if (!queue_delayed_work(fw_workqueue, &r->work, delay))
		client_put(r->client);
}