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
struct cardinfo {TYPE_1__* battery; } ;
struct TYPE_2__ {scalar_t__ good; scalar_t__ warned; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FAULT ; 
 int /*<<< orphan*/  LED_FLASH_3_5 ; 
 int /*<<< orphan*/  LED_FLASH_7_0 ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  LED_ON ; 
 int /*<<< orphan*/  set_led (struct cardinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_fault_to_battery_status(struct cardinfo *card)
{
	if (card->battery[0].good && card->battery[1].good)
		set_led(card, LED_FAULT, LED_OFF);
	else if (card->battery[0].warned || card->battery[1].warned)
		set_led(card, LED_FAULT, LED_ON);
	else if (!card->battery[0].good && !card->battery[1].good)
		set_led(card, LED_FAULT, LED_FLASH_7_0);
	else
		set_led(card, LED_FAULT, LED_FLASH_3_5);
}