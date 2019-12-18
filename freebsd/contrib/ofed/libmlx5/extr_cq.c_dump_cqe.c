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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int,int) ; 

__attribute__((used)) static void dump_cqe(FILE *fp, void *buf)
{
	uint32_t *p = buf;
	int i;

	for (i = 0; i < 16; i += 4)
		fprintf(fp, "%08x %08x %08x %08x\n", be32toh(p[i]), be32toh(p[i + 1]),
			be32toh(p[i + 2]), be32toh(p[i + 3]));
}