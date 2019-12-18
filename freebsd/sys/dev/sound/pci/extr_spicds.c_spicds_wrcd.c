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
typedef  int u_int16_t ;
struct spicds_info {scalar_t__ type; int /*<<< orphan*/  devinfo; int /*<<< orphan*/  (* ctrl ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;scalar_t__ cif; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ SPICDS_TYPE_AK4381 ; 
 scalar_t__ SPICDS_TYPE_AK4396 ; 
 scalar_t__ SPICDS_TYPE_WM8770 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  spicds_wrbit (struct spicds_info*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spicds_wrcd(struct spicds_info *codec, int reg, u_int16_t val)
{
	int mask;

#if(0)
	device_printf(codec->dev, "spicds_wrcd(codec, 0x%02x, 0x%02x)\n", reg, val);
#endif
	/* start */
	if (codec->cif)
		codec->ctrl(codec->devinfo, 1, 1, 0);
	else
		codec->ctrl(codec->devinfo, 0, 1, 0);
	DELAY(1);
	if (codec->type != SPICDS_TYPE_WM8770) {
	if (codec->type == SPICDS_TYPE_AK4381) {
	/* AK4381 chip address */
        spicds_wrbit(codec, 0);
        spicds_wrbit(codec, 1);
	}
	else if (codec->type == SPICDS_TYPE_AK4396)
	{
	/* AK4396 chip address */
        spicds_wrbit(codec, 0);
        spicds_wrbit(codec, 0);
	}
	else {
	/* chip address */
	spicds_wrbit(codec, 1);
	spicds_wrbit(codec, 0);
	}
	/* write */
	spicds_wrbit(codec, 1);
	/* register address */
	for (mask = 0x10; mask != 0; mask >>= 1)
		spicds_wrbit(codec, reg & mask);
	/* data */
	for (mask = 0x80; mask != 0; mask >>= 1)
		spicds_wrbit(codec, val & mask);
	/* stop */
	DELAY(1);
	}
	else {
        /* register address */
        for (mask = 0x40; mask != 0; mask >>= 1)
                spicds_wrbit(codec, reg & mask);
        /* data */
        for (mask = 0x100; mask != 0; mask >>= 1)
                spicds_wrbit(codec, val & mask);
        /* stop */
        DELAY(1);
	}
	if (codec->cif) {
		codec->ctrl(codec->devinfo, 0, 1, 0);
		DELAY(1);
		codec->ctrl(codec->devinfo, 1, 1, 0);
	}
	else {
		codec->ctrl(codec->devinfo, 1, 1, 0);
	}

	return;
}