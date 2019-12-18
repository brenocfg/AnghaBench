#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drbd_connection {int /*<<< orphan*/  receiver_plug; } ;
struct TYPE_2__ {int /*<<< orphan*/ * plug; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_finish_plug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_start_plug (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 

__attribute__((used)) static void drbd_unplug_all_devices(struct drbd_connection *connection)
{
	if (current->plug == &connection->receiver_plug) {
		blk_finish_plug(&connection->receiver_plug);
		blk_start_plug(&connection->receiver_plug);
	} /* else: maybe just schedule() ?? */
}