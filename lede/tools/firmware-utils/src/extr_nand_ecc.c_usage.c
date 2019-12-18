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

/* Variables and functions */
 int DEF_NAND_ECC_OFFSET ; 
 int DEF_NAND_OOB_SIZE ; 
 int DEF_NAND_PAGE_SIZE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

void usage(const char *prog)
{
	fprintf(stderr, "Usage: %s [options] <input> <output>\n"
		"Options:\n"
		"    -p <pagesize>      NAND page size (default: %d)\n"
		"    -o <oobsize>       NAND OOB size (default: %d)\n"
		"    -e <offset>        NAND ECC offset (default: %d)\n"
		"\n", prog, DEF_NAND_PAGE_SIZE, DEF_NAND_OOB_SIZE,
		DEF_NAND_ECC_OFFSET);
	exit(1);
}