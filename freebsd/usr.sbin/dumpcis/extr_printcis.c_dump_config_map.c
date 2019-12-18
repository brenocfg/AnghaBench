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
struct tuple {int* data; scalar_t__ code; unsigned int length; } ;

/* Variables and functions */
 scalar_t__ CIS_CONF_MAP ; 
 int parse_num (unsigned int,int*,int**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
dump_config_map(struct tuple *tp)
{
	u_char *p = tp->data, x;
	unsigned int rlen, mlen = 0, i;

	rlen = (p[0] & 3) + 1;
	if (tp->code == CIS_CONF_MAP)
		mlen = ((p[0] >> 2) & 3) + 1;
	if (tp->length < rlen + mlen + 2) {
		printf("\tWrong length for configuration map tuple\n");
		return;
	}
	printf("\tReg len = %d, config register addr = 0x%x, last config = 0x%x\n",
	       rlen, parse_num(rlen | 0x10, p + 2, &p, 0), p[1]);
	if (mlen) {
		printf("\tRegisters: ");
		for (i = 0; i < mlen; i++, p++) {
			for (x = 0x1; x; x <<= 1)
				printf("%c", x & *p ? 'X' : '-');
			putchar(' ');
		}
	}
	i = tp->length - (rlen + mlen + 2);
	if (i) {
		if (!mlen)
			putchar('\t');
		printf("%d bytes in subtuples", i);
	}
	if (mlen || i)
		putchar('\n');
}