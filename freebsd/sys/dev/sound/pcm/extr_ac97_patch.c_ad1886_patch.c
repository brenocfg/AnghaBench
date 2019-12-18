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
 int /*<<< orphan*/  AC97_AD_JACK_SPDIF ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int /*<<< orphan*/ ,int) ; 

void ad1886_patch(struct ac97_info* codec)
{
#define AC97_AD_JACK_SPDIF 0x72
	/*
	 *    Presario700 workaround
	 *     for Jack Sense/SPDIF Register misetting causing
	 *    no audible output
	 *    by Santiago Nullo 04/05/2002
	 */
	ac97_wrcd(codec, AC97_AD_JACK_SPDIF, 0x0010);
}