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
struct ac97_info {int dummy; } ;

/* Variables and functions */
 int AC97_MIXEXT_CLFE ; 
 int AC97_REG_POWER ; 
 int ac97_getsubvendor (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int,int) ; 

void cmi9739_patch(struct ac97_info* codec)
{
	/*
	 * Few laptops need extra register initialization
	 * to power up the internal speakers.
	 */
	switch (ac97_getsubvendor(codec)) {
	case 0x18431043:	/* ASUS W1000N */
		ac97_wrcd(codec, AC97_REG_POWER, 0x000f);
		ac97_wrcd(codec, AC97_MIXEXT_CLFE, 0x0000);
		ac97_wrcd(codec, 0x64, 0x7110);
		break;
	default:
		break;
	}
}