#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct he_dev {unsigned long long tx_numbuffs; TYPE_1__* atm_dev; } ;
struct TYPE_2__ {unsigned int link_rate; } ;

/* Variables and functions */
 int ATM_OC3_PCR ; 
 scalar_t__ CONFIG_RCMABR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RTGTBL_OFFSET ; 
 int /*<<< orphan*/  he_writel_rcm (struct he_dev*,int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (unsigned int***) ; 
 unsigned int*** kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int he_init_cs_block_rcm(struct he_dev *he_dev)
{
	unsigned (*rategrid)[16][16];
	unsigned rate, delta;
	int i, j, reg;

	unsigned rate_atmf, exp, man;
	unsigned long long rate_cps;
	int mult, buf, buf_limit = 4;

	rategrid = kmalloc( sizeof(unsigned) * 16 * 16, GFP_KERNEL);
	if (!rategrid)
		return -ENOMEM;

	/* initialize rate grid group table */

	for (reg = 0x0; reg < 0xff; ++reg)
		he_writel_rcm(he_dev, 0x0, CONFIG_RCMABR + reg);

	/* initialize rate controller groups */

	for (reg = 0x100; reg < 0x1ff; ++reg)
		he_writel_rcm(he_dev, 0x0, CONFIG_RCMABR + reg);
	
	/* initialize tNrm lookup table */

	/* the manual makes reference to a routine in a sample driver
	   for proper configuration; fortunately, we only need this
	   in order to support abr connection */
	
	/* initialize rate to group table */

	rate = he_dev->atm_dev->link_rate;
	delta = rate / 32;

	/*
	 * 2.4 transmit internal functions
	 * 
	 * we construct a copy of the rate grid used by the scheduler
	 * in order to construct the rate to group table below
	 */

	for (j = 0; j < 16; j++) {
		(*rategrid)[0][j] = rate;
		rate -= delta;
	}

	for (i = 1; i < 16; i++)
		for (j = 0; j < 16; j++)
			if (i > 14)
				(*rategrid)[i][j] = (*rategrid)[i - 1][j] / 4;
			else
				(*rategrid)[i][j] = (*rategrid)[i - 1][j] / 2;

	/*
	 * 2.4 transmit internal function
	 *
	 * this table maps the upper 5 bits of exponent and mantissa
	 * of the atm forum representation of the rate into an index
	 * on rate grid  
	 */

	rate_atmf = 0;
	while (rate_atmf < 0x400) {
		man = (rate_atmf & 0x1f) << 4;
		exp = rate_atmf >> 5;

		/* 
			instead of '/ 512', use '>> 9' to prevent a call
			to divdu3 on x86 platforms
		*/
		rate_cps = (unsigned long long) (1UL << exp) * (man + 512) >> 9;

		if (rate_cps < 10)
			rate_cps = 10;	/* 2.2.1 minimum payload rate is 10 cps */

		for (i = 255; i > 0; i--)
			if ((*rategrid)[i/16][i%16] >= rate_cps)
				break;	 /* pick nearest rate instead? */

		/*
		 * each table entry is 16 bits: (rate grid index (8 bits)
		 * and a buffer limit (8 bits)
		 * there are two table entries in each 32-bit register
		 */

#ifdef notdef
		buf = rate_cps * he_dev->tx_numbuffs /
				(he_dev->atm_dev->link_rate * 2);
#else
		/* this is pretty, but avoids _divdu3 and is mostly correct */
		mult = he_dev->atm_dev->link_rate / ATM_OC3_PCR;
		if (rate_cps > (272ULL * mult))
			buf = 4;
		else if (rate_cps > (204ULL * mult))
			buf = 3;
		else if (rate_cps > (136ULL * mult))
			buf = 2;
		else if (rate_cps > (68ULL * mult))
			buf = 1;
		else
			buf = 0;
#endif
		if (buf > buf_limit)
			buf = buf_limit;
		reg = (reg << 16) | ((i << 8) | buf);

#define RTGTBL_OFFSET 0x400
	  
		if (rate_atmf & 0x1)
			he_writel_rcm(he_dev, reg,
				CONFIG_RCMABR + RTGTBL_OFFSET + (rate_atmf >> 1));

		++rate_atmf;
	}

	kfree(rategrid);
	return 0;
}