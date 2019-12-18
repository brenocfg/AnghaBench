#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u_long ;
typedef  TYPE_1__* res_state ;
struct TYPE_3__ {unsigned int options; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* p_option (unsigned int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

void
fp_resstat(const res_state statp, FILE *file) {
	u_long mask;

	fprintf(file, ";; res options:");
	for (mask = 1;  mask != 0U;  mask <<= 1)
		if (statp->options & mask)
			fprintf(file, " %s", p_option(mask));
	putc('\n', file);
}