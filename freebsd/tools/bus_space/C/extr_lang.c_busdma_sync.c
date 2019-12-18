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
typedef  int /*<<< orphan*/  busdma_md_t ;

/* Variables and functions */
 int bd_sync (int /*<<< orphan*/ ,int,unsigned long,unsigned long) ; 

int
busdma_sync(busdma_md_t md, int op)
{

	return (bd_sync(md, op, 0UL, ~0UL));
}