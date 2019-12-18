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
struct spicds_info {scalar_t__ type; int format; int dvc; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4524_DVC ; 
 int /*<<< orphan*/  AK4524_FORMAT ; 
 int /*<<< orphan*/  AK4524_RESET ; 
 int AK452X_RESET_RSAD ; 
 int AK452X_RESET_RSDA ; 
 scalar_t__ SPICDS_TYPE_WM8770 ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spicds_wrcd (struct spicds_info*,int /*<<< orphan*/ ,int) ; 

void
spicds_reinit(struct spicds_info *codec)
{
	snd_mtxlock(codec->lock);
	if (codec->type != SPICDS_TYPE_WM8770) {
		/* reset */
		spicds_wrcd(codec, AK4524_RESET, 0);
		/* set parameter */
		spicds_wrcd(codec, AK4524_FORMAT, codec->format);
		spicds_wrcd(codec, AK4524_DVC, codec->dvc);
		/* free reset register */
		spicds_wrcd(codec, AK4524_RESET,
		    AK452X_RESET_RSDA | AK452X_RESET_RSAD);
	} else {
		/* WM8770 reinit */
		/* AK4358 reinit */
		/* AK4381 reinit */
	}
	snd_mtxunlock(codec->lock);
}