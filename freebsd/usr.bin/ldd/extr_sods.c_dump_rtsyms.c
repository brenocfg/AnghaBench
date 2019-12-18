#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long nz_size; int /*<<< orphan*/  nlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_sym (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* rtsym_base ; 
 unsigned long rtsym_count ; 
 char rtsym_name (unsigned long) ; 
 scalar_t__* rtsym_used ; 

__attribute__((used)) static void
dump_rtsyms(void)
{
    unsigned long i;

    printf("  Run-time symbols:\n");
    for (i = 0;  i < rtsym_count;  ++i) {
	printf("    %6lu%c ", i, rtsym_used[i] ? '*' : ' ');
	dump_sym(&rtsym_base[i].nlist);
	printf("/%-5ld %s\n", rtsym_base[i].nz_size, rtsym_name(i));
    }
}