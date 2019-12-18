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
struct snd_midi {int dummy; } ;
struct mpu401 {int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int MPUFOI_UNINIT (struct mpu401*,int /*<<< orphan*/ ) ; 

int
mpu401_muninit(struct snd_midi *sm, void *arg)
{
	struct mpu401 *m = arg;

	return MPUFOI_UNINIT(m, m->cookie);
}