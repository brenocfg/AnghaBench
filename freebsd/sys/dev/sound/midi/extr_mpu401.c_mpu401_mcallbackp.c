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

/* Variables and functions */
 int /*<<< orphan*/  mpu401_mcallback (struct snd_midi*,void*,int) ; 

__attribute__((used)) static void
mpu401_mcallbackp(struct snd_midi *sm, void *arg, int flags)
{
/*	printf("mpu401_callbackp\n"); */
	mpu401_mcallback(sm, arg, flags);
}