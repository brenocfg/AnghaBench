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
struct tuple {int* data; int length; scalar_t__ code; } ;

/* Variables and functions */
 scalar_t__ CIS_CONFIG ; 
 int CIS_FEAT_IRQ ; 
 int CIS_FEAT_I_O ; 
 scalar_t__ CIS_FEAT_MEMORY (int) ; 
 int CIS_FEAT_MISC ; 
 int CIS_FEAT_POWER (int) ; 
 int CIS_FEAT_TIMING ; 
 int CIS_READY_SCALE (int) ; 
 int CIS_RESERVED_SCALE (int) ; 
 int CIS_WAIT_SCALE (int) ; 
 int /*<<< orphan*/  print_ext_speed (int /*<<< orphan*/ ,int) ; 
 int* print_io_map (int*,int*) ; 
 int* print_irq_map (int*,int*) ; 
 int* print_mem_map (int,int*,int*) ; 
 int /*<<< orphan*/  print_pwr_desc (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
dump_cis_config(struct tuple *tp)
{
	u_char *p, *q, feat;
	int     i, j;
	char    c;

	p = tp->data;
	q = p + tp->length;
	printf("\tConfig index = 0x%x%s\n", *p & 0x3F,
	       *p & 0x40 ? "(default)" : "");

	/* Interface byte exists */
	if (tp->code == CIS_CONFIG && (*p & 0x80)) {
		p++;
		printf("\tInterface byte = 0x%x ", *p);
		switch (*p & 0xF) { /* Interface type */
		default:
			printf("(reserved)");
			break;
		case 0:
			printf("(memory)");
			break;
		case 1:
			printf("(I/O)");
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			printf("(custom)");
			break;
		}
		c = ' ';
		if (*p & 0x10) { /* Battery voltage detect */
			printf(" BVD1/2 active");
			c = ',';
		}
		if (*p & 0x20) { /* Write protect active */
			printf("%c card WP active", c);	/* Write protect */
			c = ',';
		}
		if (*p & 0x40) { /* RdyBsy active bit */
			printf("%c +RDY/-BSY active", c);
			c = ',';
		}
		if (*p & 0x80)	/* Wait signal required */
			printf("%c wait signal supported", c);
		printf("\n");
	}

	/* features byte */
	p++;
	feat = *p++;

	/* Power structure sub-tuple */
	switch (CIS_FEAT_POWER(feat)) {	/* Power sub-tuple(s) exists */
	case 0:
		break;
	case 1:
		printf("\tVcc pwr:\n");
		p += print_pwr_desc(p);
		break;
	case 2:
		printf("\tVcc pwr:\n");
		p += print_pwr_desc(p);
		printf("\tVpp pwr:\n");
		p += print_pwr_desc(p);
		break;
	case 3:
		printf("\tVcc pwr:\n");
		p += print_pwr_desc(p);
		printf("\tVpp1 pwr:\n");
		p += print_pwr_desc(p);
		printf("\tVpp2 pwr:\n");
		p += print_pwr_desc(p);
		break;
	}

	/* Timing sub-tuple */
	if (tp->code == CIS_CONFIG &&
	    (feat & CIS_FEAT_TIMING)) {	/* Timing sub-tuple exists */
		i = *p++;
		j = CIS_WAIT_SCALE(i);
		if (j != 3) {
			printf("\tWait scale ");
			print_ext_speed(*p++, j);
			printf("\n");
		}
		j = CIS_READY_SCALE(i);
		if (j != 7) {
			printf("\tRDY/BSY scale ");
			print_ext_speed(*p++, j);
			printf("\n");
		}
		j = CIS_RESERVED_SCALE(i);
		if (j != 7) {
			printf("\tExternal scale ");
			print_ext_speed(*p++, j);
			printf("\n");
		}
	}

	/* I/O mapping sub-tuple */
	if (feat & CIS_FEAT_I_O) { /* I/O space sub-tuple exists */
		if (tp->code == CIS_CONFIG)
			p = print_io_map(p, q);
		else {		/* CIS_CONFIG_CB */
			printf("\tI/O base:");
			for (i = 0; i < 8; i++)
				if (*p & (1 << i))
					printf(" %d", i);
			putchar('\n');
			p++;
		}
	}

	/* IRQ descriptor sub-tuple */
	if (feat & CIS_FEAT_IRQ) /* IRQ sub-tuple exists */
		p = print_irq_map(p, q);

	/* Memory map sub-tuple */
	if (CIS_FEAT_MEMORY(feat)) { /* Memory space sub-tuple(s) exists */
		if (tp->code == CIS_CONFIG)
			p = print_mem_map(feat, p, q);
		else {		/* CIS_CONFIG_CB */
			printf("\tMemory base:");
			for (i = 0; i < 8; i++)
				if (*p & (1 << i))
					printf(" %d", i);
			putchar('\n');
			p++;
		}
	}

	/* Misc sub-tuple */
	if (feat & CIS_FEAT_MISC) { /* Miscellaneous sub-tuple exists */
		if (tp->code == CIS_CONFIG) {
			printf("\tMax twin cards = %d\n", *p & 7);
			printf("\tMisc attr:%s%s%s",
			       (*p & 8) ? " (Audio-BVD2)" : "",
			       (*p & 0x10) ? " (Read-only)" : "",
			       (*p & 0x20) ? " (Power down supported)" : "");
			if (*p++ & 0x80) {
				printf(" (Ext byte = 0x%x)", *p);
				p++;
			}
			putchar('\n');
		}
		else {		/* CIS_CONFIG_CB */
			printf("\tMisc attr:");
			printf("%s%s%s%s%s%s%s",
			       (*p & 1) ? " (Master)" : "",
			       (*p & 2) ? " (Invalidate)" : "",
			       (*p & 4) ? " (VGA palette)" : "",
			       (*p & 8) ? " (Parity)" : "",
			       (*p & 0x10) ? " (Wait)" : "",
			       (*p & 0x20) ? " (Serr)" : "",
			       (*p & 0x40) ? " (Fast back)" : "");
			if (*p++ & 0x80) {
				printf("%s%s",
				       (*p & 1) ? " (Binary audio)" : "",
				       (*p & 2) ? " (pwm audio)" : "");
				p++;
			}
			putchar('\n');
		}
	}
}