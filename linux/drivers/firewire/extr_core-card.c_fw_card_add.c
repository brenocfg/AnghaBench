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
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u32 ;
struct fw_card {int /*<<< orphan*/  link; TYPE_1__* driver; int /*<<< orphan*/  guid; void* link_speed; void* max_receive; } ;
struct TYPE_2__ {int (* enable ) (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  card_list ; 
 int /*<<< orphan*/  card_mutex ; 
 int /*<<< orphan*/  config_rom_length ; 
 int /*<<< orphan*/  generate_config_rom (struct fw_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmp_config_rom ; 

int fw_card_add(struct fw_card *card,
		u32 max_receive, u32 link_speed, u64 guid)
{
	int ret;

	card->max_receive = max_receive;
	card->link_speed = link_speed;
	card->guid = guid;

	mutex_lock(&card_mutex);

	generate_config_rom(card, tmp_config_rom);
	ret = card->driver->enable(card, tmp_config_rom, config_rom_length);
	if (ret == 0)
		list_add_tail(&card->link, &card_list);

	mutex_unlock(&card_mutex);

	return ret;
}