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
struct ttyinq_block {char* tib_data; } ;
struct ttyinq {int ti_linestart; int ti_end; struct ttyinq_block* ti_lastblock; } ;

/* Variables and functions */
 int GETBIT (struct ttyinq_block*,unsigned int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int TTYINQ_DATASIZE ; 

int
ttyinq_peekchar(struct ttyinq *ti, char *c, int *quote)
{
	unsigned int boff;
	struct ttyinq_block *tib = ti->ti_lastblock;

	if (ti->ti_linestart == ti->ti_end)
		return (-1);

	MPASS(ti->ti_end > 0);
	boff = (ti->ti_end - 1) % TTYINQ_DATASIZE;

	*c = tib->tib_data[boff];
	*quote = GETBIT(tib, boff);

	return (0);
}