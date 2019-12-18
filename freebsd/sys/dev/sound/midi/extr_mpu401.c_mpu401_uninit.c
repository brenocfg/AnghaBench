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
struct mpu401 {int /*<<< orphan*/  mid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (struct mpu401*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPU_RESET ; 
 int /*<<< orphan*/  M_MIDI ; 
 int /*<<< orphan*/  free (struct mpu401*,int /*<<< orphan*/ ) ; 
 int midi_uninit (int /*<<< orphan*/ ) ; 

int
mpu401_uninit(struct mpu401 *m)
{
	int retval;

	CMD(m, MPU_RESET);
	retval = midi_uninit(m->mid);
	if (retval)
		return retval;
	free(m, M_MIDI);
	return 0;
}