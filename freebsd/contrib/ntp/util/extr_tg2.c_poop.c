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
 scalar_t__ BUFLNG ; 
#define  HIGH 129 
#define  LOW 128 
 int OFF ; 
 scalar_t__ bufcnt ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/ * u3000 ; 
 int /*<<< orphan*/ * u6000 ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

void poop(
	int	pulse,		/* pulse length (ms) */
	int	freq,		/* frequency (Hz) */
	int	amp,		/* amplitude */
	int inverted	/* is upside down */
	)
{
	int	increm;		/* phase increment */
	int	i, j;

	if (amp == OFF || freq == 0)
		increm = 10;
	else
		increm = freq / 100;
	j = 0;
	for (i = 0 ; i < pulse * 8; i++) {
		switch (amp) {

		case HIGH:
			if  (inverted)
				buffer[bufcnt++] = ~u3000[j];
			else
				buffer[bufcnt++] = ~u6000[j];
			break;

		case LOW:
			if  (inverted)
				buffer[bufcnt++] = ~u6000[j];
			else
				buffer[bufcnt++] = ~u3000[j];
			break;

		default:
			buffer[bufcnt++] = ~0;
		}
		if (bufcnt >= BUFLNG) {
			write(fd, buffer, BUFLNG);
			bufcnt = 0;
		}
		j = (j + increm) % 80;
	}
}