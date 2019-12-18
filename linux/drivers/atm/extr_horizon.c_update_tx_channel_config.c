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
typedef  short u8 ;
typedef  short u16 ;
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  TX_CHANNEL_CONFIG_COMMAND_OFF ; 
 int /*<<< orphan*/  TX_CHANNEL_CONFIG_DATA_OFF ; 
 short TX_CHANNEL_CONFIG_MULT ; 
 int /*<<< orphan*/  wr_regw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,short) ; 

__attribute__((used)) static inline void update_tx_channel_config (hrz_dev * dev, short chan, u8 mode, u16 value) {
  wr_regw (dev, TX_CHANNEL_CONFIG_COMMAND_OFF,
	   chan * TX_CHANNEL_CONFIG_MULT | mode);
    wr_regw (dev, TX_CHANNEL_CONFIG_DATA_OFF, value);
    return;
}