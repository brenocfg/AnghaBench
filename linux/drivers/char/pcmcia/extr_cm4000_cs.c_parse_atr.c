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
struct cm4000_dev {int atr_len; int* atr; int proto; int ta1; int atr_csum; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (int,struct cm4000_dev*,char*,...) ; 
 int /*<<< orphan*/  IS_ANY_T0 ; 
 int /*<<< orphan*/  IS_ANY_T1 ; 
 int /*<<< orphan*/  IS_BAD_CSUM ; 
 int /*<<< orphan*/  IS_INVREV ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t i ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_atr(struct cm4000_dev *dev)
{
	unsigned char any_t1, any_t0;
	unsigned char ch, ifno;
	int ix, done;

	DEBUGP(3, dev, "-> parse_atr: dev->atr_len = %i\n", dev->atr_len);

	if (dev->atr_len < 3) {
		DEBUGP(5, dev, "parse_atr: atr_len < 3\n");
		return 0;
	}

	if (dev->atr[0] == 0x3f)
		set_bit(IS_INVREV, &dev->flags);
	else
		clear_bit(IS_INVREV, &dev->flags);
	ix = 1;
	ifno = 1;
	ch = dev->atr[1];
	dev->proto = 0;		/* XXX PROTO */
	any_t1 = any_t0 = done = 0;
	dev->ta1 = 0x11;	/* defaults to 9600 baud */
	do {
		if (ifno == 1 && (ch & 0x10)) {
			/* read first interface byte and TA1 is present */
			dev->ta1 = dev->atr[2];
			DEBUGP(5, dev, "Card says FiDi is 0x%.2x\n", dev->ta1);
			ifno++;
		} else if ((ifno == 2) && (ch & 0x10)) { /* TA(2) */
			dev->ta1 = 0x11;
			ifno++;
		}

		DEBUGP(5, dev, "Yi=%.2x\n", ch & 0xf0);
		ix += ((ch & 0x10) >> 4)	/* no of int.face chars */
		    +((ch & 0x20) >> 5)
		    + ((ch & 0x40) >> 6)
		    + ((ch & 0x80) >> 7);
		/* ATRLENCK(dev,ix); */
		if (ch & 0x80) {	/* TDi */
			ch = dev->atr[ix];
			if ((ch & 0x0f)) {
				any_t1 = 1;
				DEBUGP(5, dev, "card is capable of T=1\n");
			} else {
				any_t0 = 1;
				DEBUGP(5, dev, "card is capable of T=0\n");
			}
		} else
			done = 1;
	} while (!done);

	DEBUGP(5, dev, "ix=%d noHist=%d any_t1=%d\n",
	      ix, dev->atr[1] & 15, any_t1);
	if (ix + 1 + (dev->atr[1] & 0x0f) + any_t1 != dev->atr_len) {
		DEBUGP(5, dev, "length error\n");
		return 0;
	}
	if (any_t0)
		set_bit(IS_ANY_T0, &dev->flags);

	if (any_t1) {		/* compute csum */
		dev->atr_csum = 0;
#ifdef ATR_CSUM
		for (i = 1; i < dev->atr_len; i++)
			dev->atr_csum ^= dev->atr[i];
		if (dev->atr_csum) {
			set_bit(IS_BAD_CSUM, &dev->flags);
			DEBUGP(5, dev, "bad checksum\n");
			goto return_0;
		}
#endif
		if (any_t0 == 0)
			dev->proto = 1;	/* XXX PROTO */
		set_bit(IS_ANY_T1, &dev->flags);
	}

	return 1;
}