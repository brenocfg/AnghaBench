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

/* Variables and functions */
 int BUFLNG ; 
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void delay (
	int	Delay		/* delay in samples */
	)
{
	int	samples;	/* samples remaining */

	samples = Delay;
	memset(buffer, 0, BUFLNG);
	while (samples >= BUFLNG) {
		write(fd, buffer, BUFLNG);
		samples -= BUFLNG;
	}
		write(fd, buffer, samples);
}