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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {scalar_t__ str_numstr; int /*<<< orphan*/  str_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  STR_RANDOM ; 
 int /*<<< orphan*/ * Seekpts ; 
 TYPE_1__ Tbl ; 
 scalar_t__ arc4random_uniform (scalar_t__) ; 

void
randomize(void)
{
	uint32_t cnt, i;
	off_t tmp;
	off_t *sp;

	Tbl.str_flags |= STR_RANDOM;
	cnt = Tbl.str_numstr;

	/*
	 * move things around randomly
	 */

	for (sp = Seekpts; cnt > 0; cnt--, sp++) {
		i = arc4random_uniform(cnt);
		tmp = sp[0];
		sp[0] = sp[i];
		sp[i] = tmp;
	}
}