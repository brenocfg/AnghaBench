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
struct mips_tmp_reloc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  free (struct mips_tmp_reloc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_tmp_reloc_free(struct mips_tmp_reloc *r)
{

	free(r, M_TEMP);
}