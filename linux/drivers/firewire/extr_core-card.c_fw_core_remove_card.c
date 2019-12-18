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
struct fw_card_driver {int /*<<< orphan*/  stop_iso; int /*<<< orphan*/  free_iso_context; int /*<<< orphan*/  (* update_phy_reg ) (struct fw_card*,int,int,int /*<<< orphan*/ ) ;} ;
struct fw_card {int /*<<< orphan*/  transaction_list; int /*<<< orphan*/  done; struct fw_card_driver* driver; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int PHY_CONTENDER ; 
 int PHY_LINK_ACTIVE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  card_mutex ; 
 struct fw_card_driver dummy_driver_template ; 
 int /*<<< orphan*/  fw_card_put (struct fw_card*) ; 
 int /*<<< orphan*/  fw_destroy_nodes (struct fw_card*) ; 
 int /*<<< orphan*/  fw_schedule_bus_reset (struct fw_card*,int,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fw_card*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void fw_core_remove_card(struct fw_card *card)
{
	struct fw_card_driver dummy_driver = dummy_driver_template;

	card->driver->update_phy_reg(card, 4,
				     PHY_LINK_ACTIVE | PHY_CONTENDER, 0);
	fw_schedule_bus_reset(card, false, true);

	mutex_lock(&card_mutex);
	list_del_init(&card->link);
	mutex_unlock(&card_mutex);

	/* Switch off most of the card driver interface. */
	dummy_driver.free_iso_context	= card->driver->free_iso_context;
	dummy_driver.stop_iso		= card->driver->stop_iso;
	card->driver = &dummy_driver;

	fw_destroy_nodes(card);

	/* Wait for all users, especially device workqueue jobs, to finish. */
	fw_card_put(card);
	wait_for_completion(&card->done);

	WARN_ON(!list_empty(&card->transaction_list));
}