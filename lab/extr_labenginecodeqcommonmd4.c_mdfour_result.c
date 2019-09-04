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
struct mdfour {int /*<<< orphan*/  D; int /*<<< orphan*/  C; int /*<<< orphan*/  B; int /*<<< orphan*/  A; } ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  copy4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdfour_result(struct mdfour *md, byte *out)
{
	copy4(out, md->A);
	copy4(out+4, md->B);
	copy4(out+8, md->C);
	copy4(out+12, md->D);
}