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
struct rsxx_cardinfo {int /*<<< orphan*/  config; } ;
struct TYPE_2__ {scalar_t__ version; int /*<<< orphan*/  crc; } ;
struct rsxx_card_cfg {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  CREG_ADD_CONFIG ; 
 int EINVAL ; 
 scalar_t__ RSXX_CFG_VERSION ; 
 int /*<<< orphan*/  config_data_cpu_to_le (struct rsxx_card_cfg*) ; 
 int /*<<< orphan*/  config_data_crc32 (struct rsxx_card_cfg*) ; 
 int /*<<< orphan*/  config_data_swab (struct rsxx_card_cfg*) ; 
 int /*<<< orphan*/  config_hdr_cpu_to_be (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct rsxx_card_cfg*,int /*<<< orphan*/ *,int) ; 
 int rsxx_creg_write (struct rsxx_cardinfo*,int /*<<< orphan*/ ,int,struct rsxx_card_cfg*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rsxx_save_config(struct rsxx_cardinfo *card)
{
	struct rsxx_card_cfg cfg;
	int st;

	memcpy(&cfg, &card->config, sizeof(cfg));

	if (unlikely(cfg.hdr.version != RSXX_CFG_VERSION)) {
		dev_err(CARD_TO_DEV(card),
			"Cannot save config with invalid version %d\n",
			cfg.hdr.version);
		return -EINVAL;
	}

	/* Convert data to little endian for the CRC calculation. */
	config_data_cpu_to_le(&cfg);

	cfg.hdr.crc = config_data_crc32(&cfg);

	/*
	 * Swap the data from little endian to big endian so it can be
	 * stored.
	 */
	config_data_swab(&cfg);
	config_hdr_cpu_to_be(&cfg.hdr);

	st = rsxx_creg_write(card, CREG_ADD_CONFIG, sizeof(cfg), &cfg, 1);
	if (st)
		return st;

	return 0;
}