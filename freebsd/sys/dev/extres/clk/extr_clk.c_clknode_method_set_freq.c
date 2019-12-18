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
typedef  int /*<<< orphan*/  uint64_t ;
struct clknode {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
clknode_method_set_freq(struct clknode *clknode, uint64_t fin,  uint64_t *fout,
   int flags, int *stop)
{

	*stop = 0;
	return (0);
}