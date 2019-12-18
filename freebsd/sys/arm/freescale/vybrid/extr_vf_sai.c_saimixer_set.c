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
struct sc_pcminfo {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct sc_pcminfo* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static int
saimixer_set(struct snd_mixer *m, unsigned dev,
    unsigned left, unsigned right)
{
	struct sc_pcminfo *scp;

	scp = mix_getdevinfo(m);

#if 0
	device_printf(scp->dev, "saimixer_set() %d %d\n",
	    left, right);
#endif

	return (0);
}