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
struct mpu401 {int flags; int /*<<< orphan*/  timer; scalar_t__ si; int /*<<< orphan*/  mid; } ;
typedef  int /*<<< orphan*/  MIDI_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D (int,int) ; 
 int MPU_INPUTBUSY ; 
 int MPU_INTR_BUF ; 
 int MPU_OUTPUTBUSY ; 
 int M_TXEN ; 
 int /*<<< orphan*/  READ (struct mpu401*) ; 
 int STATUS (struct mpu401*) ; 
 int /*<<< orphan*/  WRITE (struct mpu401*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct mpu401*) ; 
 int /*<<< orphan*/  midi_in (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ midi_out (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpu401_timeout ; 

__attribute__((used)) static int
mpu401_intr(struct mpu401 *m)
{
#define MPU_INTR_BUF	16
	MIDI_TYPE b[MPU_INTR_BUF];
	int i;
	int s;

/*
	printf("mpu401_intr\n");
*/
#define RXRDY(m) ( (STATUS(m) & MPU_INPUTBUSY) == 0)
#define TXRDY(m) ( (STATUS(m) & MPU_OUTPUTBUSY) == 0)
#if 0
#define D(x,l) printf("mpu401_intr %d %x %s %s\n",l, x, x&MPU_INPUTBUSY?"RX":"", x&MPU_OUTPUTBUSY?"TX":"")
#else
#define D(x,l)
#endif
	i = 0;
	s = STATUS(m);
	D(s, 1);
	while ((s & MPU_INPUTBUSY) == 0 && i < MPU_INTR_BUF) {
		b[i] = READ(m);
/*
		printf("mpu401_intr in i %d d %d\n", i, b[i]);
*/
		i++;
		s = STATUS(m);
	}
	if (i)
		midi_in(m->mid, b, i);
	i = 0;
	while (!(s & MPU_OUTPUTBUSY) && i < MPU_INTR_BUF) {
		if (midi_out(m->mid, b, 1)) {
/*
			printf("mpu401_intr out i %d d %d\n", i, b[0]);
*/

			WRITE(m, *b);
		} else {
/*
			printf("mpu401_intr write: no output\n");
*/
			return 0;
		}
		i++;
		/* DELAY(100); */
		s = STATUS(m);
	}

	if ((m->flags & M_TXEN) && (m->si)) {
		callout_reset(&m->timer, 1, mpu401_timeout, m);
	}
	return (m->flags & M_TXEN) == M_TXEN;
}