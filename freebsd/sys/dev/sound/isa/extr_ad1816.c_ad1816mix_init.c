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
struct snd_mixer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816_MIXER_DEVICES ; 
 int /*<<< orphan*/  AD1816_REC_DEVICES ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ad1816mix_init(struct snd_mixer *m)
{
	mix_setdevs(m, AD1816_MIXER_DEVICES);
	mix_setrecdevs(m, AD1816_REC_DEVICES);
	return 0;
}