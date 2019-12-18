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
struct eeh_pe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __eeh_pe_dev_mode_mark ; 
 int /*<<< orphan*/  eeh_pe_dev_traverse (struct eeh_pe*,int /*<<< orphan*/ ,int*) ; 

void eeh_pe_dev_mode_mark(struct eeh_pe *pe, int mode)
{
	eeh_pe_dev_traverse(pe, __eeh_pe_dev_mode_mark, &mode);
}