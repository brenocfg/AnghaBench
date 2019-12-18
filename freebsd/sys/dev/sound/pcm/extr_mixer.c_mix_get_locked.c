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
typedef  int /*<<< orphan*/  u_int ;
struct snd_mixer {int dummy; } ;

/* Variables and functions */
 int mixer_get (struct snd_mixer*,int /*<<< orphan*/ ) ; 

int
mix_get_locked(struct snd_mixer *m, u_int dev, int *pleft, int *pright)
{
	int level;

	level = mixer_get(m, dev);
	if (level < 0) {
		*pright = *pleft = -1;
		return (-1);
	}

	*pleft = level & 0xFF;
	*pright = (level >> 8) & 0xFF;

	return (0);
}