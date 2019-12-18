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
struct mips_tmp_reloc {struct mips_tmp_reloc* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  free (struct mips_tmp_reloc*,int /*<<< orphan*/ ) ; 
 struct mips_tmp_reloc* ml ; 

__attribute__((used)) static void
mips_tmp_reloc_flush(void)
{
	struct mips_tmp_reloc *r, *rn;

	r = ml;
	ml = NULL;
	while (r != NULL) {
		rn = r->next;
		free(r, M_TEMP);
		r = rn;
	}
}