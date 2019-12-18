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
typedef  int /*<<< orphan*/  u8 ;
struct lanai_dev {int /*<<< orphan*/  const* eeprom; } ;

/* Variables and functions */
 size_t EEPROM_MAC ; 

__attribute__((used)) static inline const u8 *eeprom_mac(const struct lanai_dev *lanai)
{
	return &lanai->eeprom[EEPROM_MAC];
}