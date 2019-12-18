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
struct spicds_info {int type; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4358_LO1ATT ; 
 unsigned int AK4358_OATT_ENABLE ; 
 int /*<<< orphan*/  AK4358_RO1ATT ; 
 int /*<<< orphan*/  AK4381_LOATT ; 
 int /*<<< orphan*/  AK4381_ROATT ; 
 int /*<<< orphan*/  AK4396_LOATT ; 
 int /*<<< orphan*/  AK4396_ROATT ; 
 int /*<<< orphan*/  AK4524_LIPGA ; 
 int /*<<< orphan*/  AK4524_LOATT ; 
 int /*<<< orphan*/  AK4524_RIPGA ; 
 int /*<<< orphan*/  AK4524_ROATT ; 
 int /*<<< orphan*/  AK4528_LOATT ; 
 int /*<<< orphan*/  AK4528_ROATT ; 
 int PCMDIR_PLAY ; 
 int PCMDIR_REC ; 
 int const SPICDS_TYPE_AK4358 ; 
#define  SPICDS_TYPE_AK4381 130 
#define  SPICDS_TYPE_AK4396 129 
 int SPICDS_TYPE_AK4524 ; 
 int SPICDS_TYPE_AK4528 ; 
#define  SPICDS_TYPE_WM8770 128 
 int /*<<< orphan*/  WM8770_AOATT_L1 ; 
 int /*<<< orphan*/  WM8770_AOATT_R1 ; 
 unsigned int WM8770_AOATT_UPDATE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_wrcd (struct spicds_info*,int /*<<< orphan*/ ,unsigned int) ; 

void
spicds_set(struct spicds_info *codec, int dir, unsigned int left, unsigned int right)
{
#if(0)
	device_printf(codec->dev, "spicds_set(codec, %d, %d, %d)\n", dir, left, right);
#endif
	snd_mtxlock(codec->lock);
	if (left >= 100)
		if ((codec->type == SPICDS_TYPE_AK4381) || \
		(codec->type == SPICDS_TYPE_AK4396))
			left = 255;
		else
			left = 127;
	else
		switch (codec->type) {
		case SPICDS_TYPE_WM8770:
			left = left + 27;
			break;
		case SPICDS_TYPE_AK4381:
		case SPICDS_TYPE_AK4396:
			left = left * 255 / 100;
			break;
		default:
			left = left * 127 / 100;
		}
	if (right >= 100)
		if ((codec->type == SPICDS_TYPE_AK4381) || \
		(codec->type == SPICDS_TYPE_AK4396))
                        right = 255;
                else
			right  = 127;
	else
		switch (codec->type) {
		case SPICDS_TYPE_WM8770:
                        right = right + 27;
			break;
		case SPICDS_TYPE_AK4381:
		case SPICDS_TYPE_AK4396:
			right = right * 255 / 100;
			break;
                default:
                        right = right * 127 / 100;
		}
	if (dir == PCMDIR_REC && codec->type == SPICDS_TYPE_AK4524) {
#if(0)
		device_printf(codec->dev, "spicds_set(): AK4524(REC) %d/%d\n", left, right);
#endif
		spicds_wrcd(codec, AK4524_LIPGA, left);
		spicds_wrcd(codec, AK4524_RIPGA, right);
	}
	if (dir == PCMDIR_PLAY && codec->type == SPICDS_TYPE_AK4524) {
#if(0)
		device_printf(codec->dev, "spicds_set(): AK4524(PLAY) %d/%d\n", left, right);
#endif
		spicds_wrcd(codec, AK4524_LOATT, left);
		spicds_wrcd(codec, AK4524_ROATT, right);
	}
	if (dir == PCMDIR_PLAY && codec->type == SPICDS_TYPE_AK4528) {
#if(0)
		device_printf(codec->dev, "spicds_set(): AK4528(PLAY) %d/%d\n", left, right);
#endif
		spicds_wrcd(codec, AK4528_LOATT, left);
		spicds_wrcd(codec, AK4528_ROATT, right);
	}
        if (dir == PCMDIR_PLAY && codec->type == SPICDS_TYPE_WM8770) {
#if(0)
                device_printf(codec->dev, "spicds_set(): WM8770(PLAY) %d/%d\n", left, right);
#endif
                spicds_wrcd(codec, WM8770_AOATT_L1, left | WM8770_AOATT_UPDATE);
                spicds_wrcd(codec, WM8770_AOATT_R1, right | WM8770_AOATT_UPDATE);
        }
        if (dir == PCMDIR_PLAY && codec->type == SPICDS_TYPE_AK4358) {
#if(0)
                device_printf(codec->dev, "spicds_set(): AK4358(PLAY) %d/%d\n", left, right);
#endif
                spicds_wrcd(codec, AK4358_LO1ATT, left | AK4358_OATT_ENABLE);
                spicds_wrcd(codec, AK4358_RO1ATT, right | AK4358_OATT_ENABLE);
        }
        if (dir == PCMDIR_PLAY && codec->type == SPICDS_TYPE_AK4381) {
#if(0)
                device_printf(codec->dev, "spicds_set(): AK4381(PLAY) %d/%d\n", left, right);
#endif
                spicds_wrcd(codec, AK4381_LOATT, left);
                spicds_wrcd(codec, AK4381_ROATT, right);
        }

        if (dir == PCMDIR_PLAY && codec->type == SPICDS_TYPE_AK4396) {
#if(0)
                device_printf(codec->dev, "spicds_set(): AK4396(PLAY) %d/%d\n", left, right);
#endif
                spicds_wrcd(codec, AK4396_LOATT, left);
                spicds_wrcd(codec, AK4396_ROATT, right);
        }

	snd_mtxunlock(codec->lock);
}