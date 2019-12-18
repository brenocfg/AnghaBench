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
typedef  int u_char ;

/* Variables and functions */
 int CIS_IRQ_IRQN (int) ; 
 int CIS_IRQ_LEVEL ; 
 int CIS_IRQ_MASK ; 
 int CIS_IRQ_PULSE ; 
 int CIS_IRQ_SHARING ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int tpl16 (int*) ; 

__attribute__((used)) static u_char *
print_irq_map(u_char *p, u_char *q)
{
	int i, j;
	u_char c;

	if (q <= p)
		goto err;
	printf("\t\tIRQ modes:");
	c = ' ';
	if (*p & CIS_IRQ_LEVEL) { /* Level triggered interrupts */
		printf(" Level");
		c = ',';
	}
	if (*p & CIS_IRQ_PULSE) { /* Pulse triggered requests */
		printf("%c Pulse", c);
		c = ',';
	}
	if (*p & CIS_IRQ_SHARING) /* Interrupt sharing */
		printf("%c Shared", c);
	putchar('\n');

	/* IRQ mask values exist */
	if (*p & CIS_IRQ_MASK) {
		if (q - p < 3)
			goto err;
		i = tpl16(p + 1); /* IRQ mask */
		printf("\t\tIRQs: ");
		if (*p & 1)
			printf(" NMI");
		if (*p & 0x2)
			printf(" IOCK");
		if (*p & 0x4)
			printf(" BERR");
		if (*p & 0x8)
			printf(" VEND");
		for (j = 0; j < 16; j++)
			if (i & (1 << j))
				printf(" %d", j);
		putchar('\n');
		p += 3;
	} else {
		printf("\t\tIRQ level = %d\n", CIS_IRQ_IRQN(*p));
		p++;
	}
	return p;

 err:	/* warning */
	printf("\tWrong length for IRQ sub-tuple\n");
	return p;
}