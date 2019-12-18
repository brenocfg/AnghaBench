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
struct snd_mixer {struct mtx* lock; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 struct mtx Giant ; 

struct mtx *
mixer_get_lock(struct snd_mixer *m)
{
	if (m->lock == NULL) {
		return (&Giant);
	}
	return (m->lock);
}