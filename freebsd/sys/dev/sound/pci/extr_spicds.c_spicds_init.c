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
struct spicds_info {scalar_t__ type; int format; int dvc; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AK4524_DVC ; 
 int AK4524_FORMAT ; 
 int AK4524_POWER ; 
 int AK4524_RESET ; 
 int AK452X_POWER_PWAD ; 
 int AK452X_POWER_PWDA ; 
 int AK452X_POWER_PWVR ; 
 int AK452X_RESET_RSAD ; 
 int AK452X_RESET_RSDA ; 
 scalar_t__ SPICDS_TYPE_AK4358 ; 
 scalar_t__ SPICDS_TYPE_AK4381 ; 
 scalar_t__ SPICDS_TYPE_AK4396 ; 
 scalar_t__ SPICDS_TYPE_AK4524 ; 
 scalar_t__ SPICDS_TYPE_AK4528 ; 
 scalar_t__ SPICDS_TYPE_WM8770 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_wrcd (struct spicds_info*,int,int) ; 

void
spicds_init(struct spicds_info *codec)
{
#if(0)
	device_printf(codec->dev, "spicds_init(codec)\n");
#endif
	snd_mtxlock(codec->lock);
	if (codec->type == SPICDS_TYPE_AK4524 ||\
	    codec->type == SPICDS_TYPE_AK4528) {
		/* power off */
		spicds_wrcd(codec, AK4524_POWER, 0);
		/* set parameter */
		spicds_wrcd(codec, AK4524_FORMAT, codec->format);
		spicds_wrcd(codec, AK4524_DVC, codec->dvc);
		/* power on */
		spicds_wrcd(codec, AK4524_POWER,
		    AK452X_POWER_PWDA | AK452X_POWER_PWAD | AK452X_POWER_PWVR);
		/* free reset register */
		spicds_wrcd(codec, AK4524_RESET,
		    AK452X_RESET_RSDA | AK452X_RESET_RSAD);
	}
	if (codec->type == SPICDS_TYPE_WM8770) {
		/* WM8770 init values are taken from ALSA */

		/* These come first to reduce init pop noise */
		spicds_wrcd(codec, 0x1b, 0x044);	/* ADC Mux (AC'97 source) */
		spicds_wrcd(codec, 0x1c, 0x00B);	/* Out Mux1 (VOUT1 = DAC+AUX, VOUT2 = DAC) */
		spicds_wrcd(codec, 0x1d, 0x009);	/* Out Mux2 (VOUT2 = DAC, VOUT3 = DAC) */

		spicds_wrcd(codec, 0x18, 0x000);	/* All power-up */

		spicds_wrcd(codec, 0x16, 0x122);	/* I2S, normal polarity, 24bit */
		spicds_wrcd(codec, 0x17, 0x022);	/* 256fs, slave mode */

		spicds_wrcd(codec, 0x19, 0x000);	/* -12dB ADC/L */
		spicds_wrcd(codec, 0x1a, 0x000);	/* -12dB ADC/R */
	}
	if (codec->type == SPICDS_TYPE_AK4358)
		spicds_wrcd(codec, 0x00, 0x07);		/* I2S, 24bit, power-up */
	if (codec->type == SPICDS_TYPE_AK4381)
		spicds_wrcd(codec, 0x00, 0x8f);		/* I2S, 24bit, power-up */
	if (codec->type == SPICDS_TYPE_AK4396)
		spicds_wrcd(codec, 0x00, 0x07);		/* I2S, 24bit, power-up */
	snd_mtxunlock(codec->lock);
}