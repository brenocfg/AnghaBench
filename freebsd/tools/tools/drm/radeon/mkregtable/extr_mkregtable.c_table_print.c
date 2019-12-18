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
struct table {int nentry; char* gpu_prefix; int* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void table_print(struct table *t)
{
	unsigned nlloop, i, j, n, c, id;

	nlloop = (t->nentry + 3) / 4;
	c = t->nentry;
	printf(
	    "#include <sys/cdefs.h>\n"
	    "__FBSDID(\"$" "FreeBSD" "$\");\n"
	    "\n"
	    );
	printf("static const unsigned %s_reg_safe_bm[%d] = {\n", t->gpu_prefix,
	       t->nentry);
	for (i = 0, id = 0; i < nlloop; i++) {
		n = 4;
		if (n > c)
			n = c;
		c -= n;
		for (j = 0; j < n; j++) {
			if (j == 0)
				printf("\t");
			else
				printf(" ");
			printf("0x%08X,", t->table[id++]);
		}
		printf("\n");
	}
	printf("};\n");
}