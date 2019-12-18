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
typedef  size_t u_int32_t ;
struct snd_mixer {int dummy; } ;
struct sc_info {int src; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENVY24HT_CHAN_PLAY_SPDIF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 int* envy24ht_mixmap ; 
 struct sc_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static u_int32_t
envy24htmixer_setrecsrc(struct snd_mixer *m, u_int32_t src)
{
	struct sc_info *sc = mix_getdevinfo(m);
	int ch = envy24ht_mixmap[src];
#if(0)
	device_printf(sc->dev, "envy24htmixer_setrecsrc(m, %d)\n", src);
#endif

	if (ch > ENVY24HT_CHAN_PLAY_SPDIF)
		sc->src = ch;
	return src;
}