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
union ieee754sp {scalar_t__ bits; } ;

/* Variables and functions */
#define  IEEE754_CLASS_DNORM 133 
#define  IEEE754_CLASS_INF 132 
#define  IEEE754_CLASS_NORM 131 
#define  IEEE754_CLASS_QNAN 130 
#define  IEEE754_CLASS_SNAN 129 
#define  IEEE754_CLASS_ZERO 128 
 scalar_t__ SPBEXP (union ieee754sp) ; 
 int SPMANT (union ieee754sp) ; 
 int /*<<< orphan*/  SPSIGN (union ieee754sp) ; 
 scalar_t__ SP_EBIAS ; 
 int /*<<< orphan*/  SP_FBITS ; 
 int SP_MBIT (int) ; 
 int ieee754sp_class (union ieee754sp) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

union ieee754sp ieee754sp_dump(char *m, union ieee754sp x)
{
	int i;

	printk("%s=", m);
	printk("<%08x>\n", (unsigned) x.bits);
	printk("\t=");
	switch (ieee754sp_class(x)) {
	case IEEE754_CLASS_QNAN:
	case IEEE754_CLASS_SNAN:
		printk("Nan %c", SPSIGN(x) ? '-' : '+');
		for (i = SP_FBITS - 1; i >= 0; i--)
			printk("%c", SPMANT(x) & SP_MBIT(i) ? '1' : '0');
		break;
	case IEEE754_CLASS_INF:
		printk("%cInfinity", SPSIGN(x) ? '-' : '+');
		break;
	case IEEE754_CLASS_ZERO:
		printk("%cZero", SPSIGN(x) ? '-' : '+');
		break;
	case IEEE754_CLASS_DNORM:
		printk("%c0.", SPSIGN(x) ? '-' : '+');
		for (i = SP_FBITS - 1; i >= 0; i--)
			printk("%c", SPMANT(x) & SP_MBIT(i) ? '1' : '0');
		printk("e%d", SPBEXP(x) - SP_EBIAS);
		break;
	case IEEE754_CLASS_NORM:
		printk("%c1.", SPSIGN(x) ? '-' : '+');
		for (i = SP_FBITS - 1; i >= 0; i--)
			printk("%c", SPMANT(x) & SP_MBIT(i) ? '1' : '0');
		printk("e%d", SPBEXP(x) - SP_EBIAS);
		break;
	default:
		printk("Illegal/Unknown IEEE754 value class");
	}
	printk("\n");
	return x;
}