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
 int CIS_FEAT_MEMORY (int) ; 
#define  CIS_FEAT_MEM_ADDR 131 
#define  CIS_FEAT_MEM_LEN 130 
#define  CIS_FEAT_MEM_NONE 129 
#define  CIS_FEAT_MEM_WIN 128 
 int CIS_MEM_ADDRSZ (int) ; 
 int CIS_MEM_HOST ; 
 int CIS_MEM_LENSZ (int) ; 
 int CIS_MEM_WINS (int) ; 
 int /*<<< orphan*/  print_num (int,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int tpl16 (int*) ; 

__attribute__((used)) static u_char *
print_mem_map(u_char feat, u_char *p, u_char *q)
{
	int i, j;
	u_char c;

	switch (CIS_FEAT_MEMORY(feat)) {

	case CIS_FEAT_MEM_NONE:	/* No memory block */
		break;
	case CIS_FEAT_MEM_LEN:	/* Specify memory length */
		if (q - p < 2)
			goto err;
		printf("\tMemory space length = 0x%x\n", tpl16(p));
		p += 2;
		break;
	case CIS_FEAT_MEM_ADDR:	/* Memory address and length */
		if (q - p < 4)
			goto err;
		printf("\tMemory space address = 0x%x, length = 0x%x\n",
		       tpl16(p + 2), tpl16(p));
		p += 4;
		break;
	case CIS_FEAT_MEM_WIN:	/* Memory descriptors. */
		if (q <= p)
			goto err;
		c = *p++;
		/* calculate byte length */
		j = CIS_MEM_LENSZ(c) + CIS_MEM_ADDRSZ(c);
		if (c & CIS_MEM_HOST)
			j += CIS_MEM_ADDRSZ(c);
		/* number of memory block */
		for (i = 0; i < CIS_MEM_WINS(c); i++) {
			if (q - p < j)
				goto err;
			printf("\tMemory descriptor %d\n\t\t", i + 1);
			/* memory length */
			p += print_num(CIS_MEM_LENSZ(c) | 0x10,
				       " blk length = 0x%x00", p, 0);
			/* card address */
			p += print_num(CIS_MEM_ADDRSZ(c) | 0x10,
				       " card addr = 0x%x00", p, 0);
			if (c & CIS_MEM_HOST) /* Host address value exist */
				p += print_num(CIS_MEM_ADDRSZ(c) | 0x10,
					       " host addr = 0x%x00", p, 0);
			putchar('\n');
		}
		break;
	}
	return p;

 err:	/* warning */
	printf("\tWrong length for memory mapping sub-tuple\n");
	return p;
}