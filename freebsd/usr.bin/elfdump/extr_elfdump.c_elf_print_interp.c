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
typedef  int u_int64_t ;
typedef  int /*<<< orphan*/  Elf32_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  P_OFFSET ; 
 int elf_get_off (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  out ; 

__attribute__((used)) static void
elf_print_interp(Elf32_Ehdr *e, void *p)
{
	u_int64_t offset;
	char *s;

	offset = elf_get_off(e, p, P_OFFSET);
	s = (char *)e + offset;
	fprintf(out, "\ninterp:\n");
	fprintf(out, "\t%s\n", s);
}