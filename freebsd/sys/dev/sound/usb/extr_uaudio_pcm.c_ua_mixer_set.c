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
typedef  int uint8_t ;
struct snd_mixer {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mix_getdevinfo (struct snd_mixer*) ; 
 struct mtx* mixer_get_lock (struct snd_mixer*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 scalar_t__ mtx_owned (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  uaudio_mixer_set (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int
ua_mixer_set(struct snd_mixer *m, unsigned type, unsigned left, unsigned right)
{
	struct mtx *mtx = mixer_get_lock(m);
	uint8_t do_unlock;

	if (mtx_owned(mtx)) {
		do_unlock = 0;
	} else {
		do_unlock = 1;
		mtx_lock(mtx);
	}
	uaudio_mixer_set(mix_getdevinfo(m), type, left, right);
	if (do_unlock) {
		mtx_unlock(mtx);
	}
	return (left | (right << 8));
}